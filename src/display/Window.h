#ifndef WINDOW_H
#define	WINDOW_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "../graphics/Pixel.h"

static const char DEFAULT_NAME[] = "Particle System Test Environment";
static const int DEFAULT_WINDOW_X = 0;
static const int DEFAULT_WINDOW_Y = 0;
static const int DEFAULT_WINDOW_W = 0;
static const int DEFAULT_WINDOW_H = 0;
static const int DEFAULT_WINDOW_FLAGS = SDL_WINDOW_FULLSCREEN_DESKTOP;
static const int DEFAULT_PIXEL_PADDING = 100; //How far out of the display a pixel can get before it is destroyed
static const bool DEFAULT_PIXEL_LINE_MODE = false;
static const bool DEFAULT_AUTO_DELETE = false;

class Window {
public:
    /// Class constructor.
    Window();
    /// Class destructor.
    virtual ~Window();
    /// Adds a pixel to the rendering cycle.
    void addPixel(Pixel pixel);
    /// Redraws the window.
    void draw();
    /// Erases all of the particles in the rendering cycle.
    void dump();
    /// \return whether or not the screen clears before it is drawn
    bool getClearing();
    /// Sets whether or not the screen clears before it is drawn.
    void setClearing(bool clearing_);
    /// \return whether or not pixels are automatically destroyed after a given interval.
    bool getAutoDelete();
    /// Sets whether or not pixels are automatically destroyed after a given interval.
    void setAutoDelete(bool autoDelete_);
private:
    void clear();
    void drawPixels();
    int width, height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Cursor* cursor;
    std::vector<Pixel>* pixels;
    bool clearing, autoDelete;
};

#endif

