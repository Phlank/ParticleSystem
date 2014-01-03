#ifndef WINDOW_H
#define	WINDOW_H

#include <SDL2/SDL.h>
#include <vector>
#include "../graphics/Pixel.h"

static const char DEFAULT_NAME[] = "Particle System Test Environment";
static const int DEFAULT_WINDOW_X = SDL_WINDOWPOS_UNDEFINED;
static const int DEFAULT_WINDOW_Y = SDL_WINDOWPOS_UNDEFINED;
static const int DEFAULT_WINDOW_W = 0;
static const int DEFAULT_WINDOW_H = 0;
static const int DEFAULT_WINDOW_FLAGS = SDL_WINDOW_FULLSCREEN_DESKTOP;
static const int DEFAULT_PIXEL_PADDING = 100; //How far out of the display a pixel can get before it is destroyed
static const bool DEFAULT_PIXEL_LINE_MODE = false;

class Window {
public:
    Window();
    virtual ~Window();
    void addPixel(Pixel pixel);
    void draw();
    void dump();
    bool getClearing();
    void setClearing(bool clearing_);
private:
    void clear();
    void drawPixels();
    int width, height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Cursor* cursor;
    std::vector<Pixel> pixels;
    bool clearing;
};

#endif

