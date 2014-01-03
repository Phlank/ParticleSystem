#include "Window.h"

Window::Window() {
    window = SDL_CreateWindow(DEFAULT_NAME, DEFAULT_WINDOW_X, DEFAULT_WINDOW_Y, DEFAULT_WINDOW_W, DEFAULT_WINDOW_H, DEFAULT_WINDOW_FLAGS);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_GetWindowSize(window, &width, &height);
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Window::addPixel(Pixel pixel) {
    pixels.push_back(pixel);
}

void Window::draw() {
    clear();
    drawPixels();
    SDL_RenderPresent(renderer);
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Window::drawPixels() {
    std::vector<Pixel>::iterator pixelIterator = pixels.begin();
    while (pixelIterator != pixels.end()) {
        int oldPixelX = pixelIterator.base()->getPosition().getX();
        int oldPixelY = pixelIterator.base()->getPosition().getY();
        pixelIterator.base()->runFrame();
        int currPixelX = pixelIterator.base()->getPosition().getX();
        int currPixelY = pixelIterator.base()->getPosition().getY();
        if (currPixelX < -DEFAULT_PIXEL_PADDING || currPixelX > width+DEFAULT_PIXEL_PADDING || currPixelY < -DEFAULT_PIXEL_PADDING || currPixelY > height+DEFAULT_PIXEL_PADDING) {
            pixels.erase(pixelIterator);
        }
        else {
            SDL_SetRenderDrawColor(renderer, pixelIterator.base()->getRed(), pixelIterator.base()->getGreen(), pixelIterator.base()->getBlue(), pixelIterator.base()->getOpacity());
            if (pixelIterator.base()->getRenderLineMode())
                SDL_RenderDrawLine(renderer, currPixelX, currPixelY, oldPixelX, oldPixelY);
            else
                SDL_RenderDrawPoint(renderer, currPixelX, currPixelY);
        }
    }
}

