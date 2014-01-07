#include "Window.h"

Window::Window() {
    window = SDL_CreateWindow(DEFAULT_NAME, DEFAULT_WINDOW_X, DEFAULT_WINDOW_Y, 640, 480, SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_ShowCursor(1);
    SDL_GetWindowSize(window, &width, &height);
    SDL_WarpMouseInWindow(window, width/2, height/2);
    clearing = DEFAULT_CLEARING;
    pixels = new std::vector<Pixel>();
    renderLine = DEFAULT_RENDER_LINE;
    antialias = DEFAULT_ANTIALIAS;
    blendmode = DEFAULT_BLENDMODE;
    clearColor = DEFAULT_CLEARCOLOR;
    clearRed = DEFAULT_CLEARRED;
    clearGreen = DEFAULT_CLEARGREEN;
    clearBlue = DEFAULT_CLEARBLUE;
    autoDelete = DEFAULT_AUTO_DELETE;
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

int Window::getBlendMode() {
    return blendmode;
}

void Window::setBlendMode(int blendmode_) {
    if (blendmode_ == 0)
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    else if (blendmode_ == 1)
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    else
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    blendmode = blendmode_;
}

bool Window::getClearColor() {
    return clearColor;
}

void Window::setClearColor(bool clearColor_) {
    if (clearColor_) {
        clearRed = 255;
        clearGreen = 255;
        clearBlue = 255;
    } else {
        clearRed = 0;
        clearGreen = 0;
        clearBlue = 0;
    }
    clearColor = clearColor_;
}

void Window::centerMouse() {
    SDL_WarpMouseInWindow(window, width/2, height/2);
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

void Window::setCursorVisible(bool option_) {
    SDL_ShowCursor(option_);
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, clearRed, clearGreen, clearBlue, 255);
    SDL_RenderClear(renderer);
}

void Window::drawPixels() {
    std::vector<Pixel>::iterator iter = pixels->begin();
    while (iter != pixels->end()) {                             //Cycles through the entire pixels vector
        Pixel* current = iter.base();                           //Makes reference to base
        Point oldPos = current->getPosition();                  //Initial position
        if (autoDelete) {
            if (!current->runPixelFrame() || oldPos.getX() < -DEFAULT_PIXEL_PADDING || oldPos.getX() > width+DEFAULT_PIXEL_PADDING || oldPos.getY() < -DEFAULT_PIXEL_PADDING || oldPos.getY() > height+DEFAULT_PIXEL_PADDING) {
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
            current->runPixelFrame();
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

/* Stuff for drawing antialiased lines. */
float ipart(float x) {
    float treasure;
    std::modf(x, &treasure);
    return treasure;
}
float round(float x) {
    return ipart(x+0.5);
}
float fpart(float x) {
    float trash;
    float treasure;
    treasure = std::modf(x, &trash);
    return treasure;
}
float rfpart(float x) {
    return 1.0-fpart(x);
}
void Window::drawAALine(double x0, double y0, Pixel* target) {
    float x1 = target->getPosition().getX();
    float y1 = target->getPosition().getY();
    float temp;
    
    Uint8 redness = target->getRed();
    Uint8 greenness = target->getGreen();
    Uint8 blueness = target->getBlue();
    Uint8 brightness = target->getOpacity();
    
    bool steep = std::abs(y1-y0) > std::abs(x1-x0);
    
    //If the line is steep, swap x and y
    if (steep) {
        temp = y0; y0 = x0; x0 = temp; //Swap
        temp = y1; y1 = x1; x1 = temp; //Swap
    }
    if (x0 > x1) {
        temp = y0; y0 = y1; y1 = temp; //Swap
        temp = x0; x0 = x1; x1 = temp; //Swap
    }
    
    //Evaluate the change between the endpoints, and the gradient slope
    float dx = x1-x0;
    float dy = y1-y0;
    float gradient = dy/dx;
    
    //Handle the first endpoint
    int xend = round(x0);
    int yend = y0+gradient*(xend-x0);
    float xgap = fpart(x0+0.5);
    float xpxl1 = xend;
    float ypxl1 = ipart(yend);
    if (steep) {
        SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, rfpart(yend)*xgap*brightness);
        SDL_RenderDrawPoint(renderer, ypxl1, xpxl1);
        SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, fpart(yend)*xgap*brightness);
        SDL_RenderDrawPoint(renderer, ypxl1+1, xpxl1);
    } else {
        SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, rfpart(yend)*xgap*brightness);
        SDL_RenderDrawPoint(renderer, xpxl1, ypxl1);
        SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, fpart(yend)*xgap*brightness);
        SDL_RenderDrawPoint(renderer, xpxl1, ypxl1+1);
    }
    float intery = yend+gradient; //First y-intersection for the main loop
    
    //Handle the second endpoint
    xend = round(x1);
    yend = y1+gradient*(xend-x1);
    xgap = fpart(x1 + 0.5);
    float xpxl2 = xend; //this will be used in the main loop
    float ypxl2 = ipart(yend);
    if (steep) {
        SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, rfpart(yend)*xgap*brightness);
        SDL_RenderDrawPoint(renderer, ypxl2, xpxl2);
        SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, fpart(yend)*xgap*brightness);
        SDL_RenderDrawPoint(renderer, ypxl2+1, xpxl2);
    } else {
        SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, rfpart(yend)*xgap*brightness);
        SDL_RenderDrawPoint(renderer, xpxl2, ypxl2);
        SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, fpart(yend)*xgap*brightness);
        SDL_RenderDrawPoint(renderer, xpxl2+1, ypxl2+1);
    }
    
    // main loop
    int x;
    for (x = xpxl1+1; x < xpxl2; x++) {
        if (steep) {
            SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, rfpart(intery)*brightness);
            SDL_RenderDrawPoint(renderer, ipart(intery), x);
            SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, fpart(intery)*brightness);
            SDL_RenderDrawPoint(renderer, ipart(intery)+1, x);
        } else {
            SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, rfpart(intery)*brightness);
            SDL_RenderDrawPoint(renderer, x, ipart(intery));
            SDL_SetRenderDrawColor(renderer, redness, greenness, blueness, fpart(intery)*brightness);
            SDL_RenderDrawPoint(renderer, x, ipart(intery)+1);
        }
        intery = intery+gradient;
    }
    
}

