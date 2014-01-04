#include "Window.h"

Window::Window() {
    window = SDL_CreateWindow(DEFAULT_NAME, DEFAULT_WINDOW_X, DEFAULT_WINDOW_Y, 640, 480, SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_GetWindowSize(window, &width, &height);
    SDL_WarpMouseInWindow(window, width/2, height/2);
    clearing = DEFAULT_CLEARING;
    pixels = new std::vector<Pixel>();
    renderLine = DEFAULT_RENDER_LINE;
    antialias = DEFAULT_ANTIALIAS;
    blendmode = DEFAULT_BLENDMODE;
}

Window::~Window() {
    pixels = NULL;
    delete(pixels);
    cursor = NULL;
    SDL_FreeCursor(cursor);
    renderer = NULL;
    SDL_DestroyRenderer(renderer);
    window = NULL;
    SDL_DestroyWindow(window);
}

void Window::addPixel(Pixel pixel) {
    pixels->push_back(pixel);
}

void Window::draw() {
    if (clearing) clear();
    drawPixels();
    SDL_RenderPresent(renderer);
}

void Window::dump() {
    pixels->erase(pixels->begin(), pixels->end());
}

bool Window::getClearing() {
    return clearing;
}

void Window::setClearing(bool clearing_) {
    clearing = clearing_;
}

bool Window::getAutoDelete() {
    return autoDelete;
}

void Window::setAutoDelete(bool autoDelete_) {
    autoDelete = autoDelete_;
}

bool Window::getRenderLine() {
    return renderLine;
}

void Window::setRenderLine(bool renderLine_) {
    renderLine = renderLine_;
}

bool Window::getAntialias() {
    return antialias;
}

void Window::setAntialias(bool antialias_) {
    antialias = antialias_;
}

bool Window::getBlendMode() {
    return blendmode;
}

void Window::setBlendMode(bool blendmode_) {
    if (blendmode_)
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    else
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    blendmode = blendmode_;
}

void Window::centerMouse() {
    SDL_WarpMouseInWindow(window, width/2, height/2);
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Window::drawPixels() {
    std::vector<Pixel>::iterator iter = pixels->begin();
    while (iter != pixels->end()) {                             //Cycles through the entire pixels vector
        Pixel* current = iter.base();                           //Makes reference to base
        Point oldPos = current->getPosition();                  //Initial position
        if (autoDelete) {
            if (!current->runFrame() || oldPos.getX() < -DEFAULT_PIXEL_PADDING || oldPos.getX() > width+DEFAULT_PIXEL_PADDING || oldPos.getY() < -DEFAULT_PIXEL_PADDING || oldPos.getY() > height+DEFAULT_PIXEL_PADDING) {
                iter = pixels->erase(iter);
            }
            else {
                Point newPos = current->getPosition();
                SDL_SetRenderDrawColor(renderer, current->getRed(), current->getGreen(), current->getBlue(), current->getOpacity());
                if (renderLine) {
                    if (antialias) {
                        drawAALine(oldPos.getX(), oldPos.getY(), current);
                    }
                    else {
                        SDL_RenderDrawLine(renderer, oldPos.getX(), oldPos.getY(), newPos.getX(), newPos.getY());
                    }
                }
                else {
                    SDL_RenderDrawPoint(renderer, newPos.getX(), newPos.getY());
                }
                iter++;
            }
        }
        else {
            current->runFrame();
            Point newPos = current->getPosition();
            SDL_SetRenderDrawColor(renderer, current->getRed(), current->getGreen(), current->getBlue(), current->getOpacity());
            if (renderLine)
                if (antialias) {
                    drawAALine(oldPos.getX(), oldPos.getY(), current);
                }
                else {
                        SDL_RenderDrawLine(renderer, oldPos.getX(), oldPos.getY(), newPos.getX(), newPos.getY());
                }
            else
                SDL_RenderDrawPoint(renderer, newPos.getX(), newPos.getY());
            iter++;
        }
    }
}

void Window::drawAALine(double x1, double y1, Pixel* target) {
    int erracc = 0, erradj;
    int erracctmp, wgt;
    int tmp, y0p1, x0pxdir;
    uint8_t a;
    
    /* Use long doubles */
    int xx0 = x1;
    int yy0 = y1;
    int xx1 = target->getPosition().getX();
    int yy1 = target->getPosition().getY();
    
    /* Reorder points if necessary */
    if (yy0 > yy1) {
        tmp = yy0;
        yy0 = yy1;
        yy1 = tmp;
        tmp = xx0;
        xx0 = xx1;
        xx1 = tmp;
    }
    
    /* Calculate distance */
    int dx = xx1-xx0;
    int dy = yy1-yy0;
    
    /* Adjust for negative dx and set xdir */
    int xdir = 1;
    if (dx < 0.0) {
        xdir = -1.0;
        dx = -dx;
    }
    
    /* Check for special cases */
    if (dx==0 || dy==0 || dx==dy) {
        SDL_SetRenderDrawColor(renderer, target->getRed(), target->getGreen(), target->getBlue(), target->getOpacity());
        SDL_RenderDrawLine(renderer, xx0, yy0, xx1, yy1);
        return;
    }
    
    int intshift = 180-4;
    
    /* Draw initial pixel */
    if (target->getOpacity() == SDL_ALPHA_OPAQUE) {
        SDL_SetRenderDrawColor(renderer, target->getRed(), target->getGreen(), target->getBlue(), target->getOpacity());
        SDL_RenderDrawPoint(renderer, x1, y1);
    }
    else {
        SDL_SetRenderDrawColor(renderer, target->getRed(), target->getGreen(), target->getBlue(), target->getOpacity());
        SDL_RenderDrawPoint(renderer, x1, y1);
    }
    
    float alpha_pp = (float)(target->getOpacity())/255;
    
    /* x-major or y-major? */
    if (dy > dx) {
        /* y-major */
        erradj = ((dx<<16)/dy)<<16;
        /* Draw all pixels other than first and last */
        x0pxdir = xx0+xdir;
        while (--dy) {
            erracctmp = erracc;
            erracc += erradj;
            if (erracc <= erracctmp) {
                /* rollover in error accumulator, x coord advances */
                xx0 = x0pxdir;
                x0pxdir += xdir;
            }
            yy0++;      /* y-major so always advance Y */
            
            /* the AAbits most significant bits of erracc give us the intensity
            weighting for this pixel, and the complement of the weighting for
            the paired pixel. */
            wgt = (erracc >> intshift) & 255;

            a = Uint8(255-wgt);
            if(target->getOpacity() != SDL_ALPHA_OPAQUE)
                a = Uint8(a*alpha_pp);
            
            SDL_SetRenderDrawColor(renderer, target->getRed(), target->getGreen(), target->getBlue(), 180);
            SDL_RenderDrawPoint(renderer, xx0, yy0);

            a = Uint8(wgt);
            if(target->getOpacity() != SDL_ALPHA_OPAQUE)
                a = Uint8(a*alpha_pp);

            SDL_SetRenderDrawColor(renderer, target->getRed(), target->getGreen(), target->getBlue(), 180);
            SDL_RenderDrawPoint(renderer, x0pxdir, yy0);
        }
    }
    else {
        /* x-major */
        erradj = ((dy<<16)/dx)<<16;
        /* Draw all pixels other than first and last */
        y0p1 = yy0+1;
        while (--dx) {
            erracctmp = erracc;
            erracc += erradj;
            if (erracc <= erracctmp) {
                /* rollover in error accumulator, y coord advances */
                yy0 = y0p1;
                y0p1++;
            }
            xx0 += xdir;      /* x-major so always advance X */
            
            /* the AAbits most significant bits of erracc give us the intensity
            weighting for this pixel, and the complement of the weighting for
            the paired pixel. */
            wgt = (erracc >> intshift) & 255;

            a = Uint8(255-wgt);
            if(target->getOpacity() != SDL_ALPHA_OPAQUE)
                a = Uint8(a*alpha_pp);
            
            SDL_SetRenderDrawColor(renderer, target->getRed(), target->getGreen(), target->getBlue(), 180);
            SDL_RenderDrawPoint(renderer, xx0, yy0);

            a = Uint8(wgt);
            if(target->getOpacity() != SDL_ALPHA_OPAQUE)
                a = Uint8(a*alpha_pp);

            SDL_SetRenderDrawColor(renderer, target->getRed(), target->getGreen(), target->getBlue(), 180);
            SDL_RenderDrawPoint(renderer, xx0, y0p1);
        }
    }
    
    /* Draw the final pixel.  Will always be perfectly intersected. */
    SDL_SetRenderDrawColor(renderer, target->getRed(), target->getGreen(), target->getBlue(), target->getOpacity());
    SDL_RenderDrawPoint(renderer, target->getPosition().getX(), target->getPosition().getY());
}

