#include "Window.h"

Window::Window() {
    window = SDL_CreateWindow(DEFAULT_NAME, DEFAULT_WINDOW_X, DEFAULT_WINDOW_Y, 640, 480, DEFAULT_WINDOW_FLAGS);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_GetWindowSize(window, &width, &height);
    SDL_WarpMouseInWindow(window, width/2, height/2);
    clearing = true;
}

Window::~Window() {
    SDL_FreeCursor(cursor);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    dump();
    pixels.~vector();
}

void Window::addPixel(Pixel pixel) {
    pixels.push_back(pixel);
}

void Window::draw() {
    if (clearing) clear();
    drawPixels();
    SDL_RenderPresent(renderer);
}

void Window::dump() {
    while (pixels.begin() != pixels.end()) {
        pixels.erase(pixels.begin());
    }
}

bool Window::getClearing() {
    return clearing;
}

void Window::setClearing(bool clearing_) {
    clearing = clearing_;
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Window::drawPixels() {
    double oldX, oldY;
    std::vector<Pixel>::iterator iter = pixels.begin();
    while (iter != pixels.end()) {
        oldX = iter.base()->getPosition().getX();
        oldY = iter.base()->getPosition().getY();
        iter.base()->runFrame();
        if (iter.base()->getPosition().getX() < -DEFAULT_PIXEL_PADDING || iter.base()->getPosition().getX() > width+DEFAULT_PIXEL_PADDING || iter.base()->getPosition().getY() < -DEFAULT_PIXEL_PADDING || iter.base()->getPosition().getY() > height+DEFAULT_PIXEL_PADDING) {
            iter = pixels.erase(iter);
        }
        else {
            SDL_SetRenderDrawColor(renderer, iter.base()->getRed(), iter.base()->getGreen(), iter.base()->getBlue(), iter.base()->getOpacity());
            if (iter.base()->getRenderLineMode())
                SDL_RenderDrawLine(renderer, oldX, oldY, iter.base()->getPosition().getX(), iter.base()->getPosition().getY());
            else
                SDL_RenderDrawPoint(renderer, iter.base()->getPosition().getX(), iter.base()->getPosition().getY());
            iter++;
        }
    }
}

