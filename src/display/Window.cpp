#include "Window.h"

Window::Window() {
    window = SDL_CreateWindow(DEFAULT_NAME, DEFAULT_WINDOW_X, DEFAULT_WINDOW_Y, 640, 480, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_GetWindowSize(window, &width, &height);
    SDL_WarpMouseInWindow(window, width/2, height/2);
    clearing = true;
    pixels = new std::vector<Pixel>();
}

Window::~Window() {
    delete(pixels);
    pixels = NULL;
    SDL_FreeCursor(cursor);
    cursor = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
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
            if (!current->runFrame()) {
                current->~Pixel();
                iter = pixels->erase(iter);
            }
            else {
                Point newPos = current->getPosition();
                SDL_SetRenderDrawColor(renderer, current->getRed(), current->getGreen(), current->getBlue(), current->getOpacity());
                if (current->getRenderLineMode())
                    SDL_RenderDrawLine(renderer, oldPos.getX(), oldPos.getY(), newPos.getX(), newPos.getY());
                else
                    SDL_RenderDrawPoint(renderer, newPos.getX(), newPos.getY());
                iter++;
            }
        }
        else {
            current->runFrame();
            Point newPos = current->getPosition();
            SDL_SetRenderDrawColor(renderer, current->getRed(), current->getGreen(), current->getBlue(), current->getOpacity());
            if (current->getRenderLineMode())
                SDL_RenderDrawLine(renderer, oldPos.getX(), oldPos.getY(), newPos.getX(), newPos.getY());
            else
                SDL_RenderDrawPoint(renderer, newPos.getX(), newPos.getY());
            iter++;
        }
    }
}

