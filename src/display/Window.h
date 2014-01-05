#ifndef WINDOW_H
#define	WINDOW_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "../graphics/Pixel.h"

static const char DEFAULT_NAME[] = "Particle System Test Environment";
static const int DEFAULT_WINDOW_X = 0;
static const int DEFAULT_WINDOW_Y = 0;
static const int DEFAULT_WINDOW_W = 0;
static const int DEFAULT_WINDOW_H = 0;
static const int DEFAULT_WINDOW_FLAGS = SDL_WINDOW_FULLSCREEN_DESKTOP;
static const int DEFAULT_PIXEL_PADDING = 0; //How far out of the display a pixel can get before it is destroyed
static const bool DEFAULT_AUTO_DELETE = false;
static const bool DEFAULT_RENDER_LINE = false;
static const bool DEFAULT_CLEARING = true;
static const bool DEFAULT_ANTIALIAS = false;
static const bool DEFAULT_BLENDMODE = false;
static const bool DEFAULT_CLEARCOLOR = false;
static const int DEFAULT_CLEARRED = 0, DEFAULT_CLEARGREEN = 0, DEFAULT_CLEARBLUE = 0;

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
    /// \return whether or not pixels are rendered as line segments.
    bool getRenderLine();
    /// Sets whether or not pixels are rendered as line segments.
    void setRenderLine(bool renderLine_);
    /// \return the antialias setting
    bool getAntialias();
    /// Sets the antialias setting
    void setAntialias(bool antialias_);
    /// \return the blendmode
    bool getBlendMode();
    /// Sets the blend mode
    void setBlendMode(bool blendmode_);
    /// \return the clearing color
    bool getClearColor();
    ///Sets the clearing color
    void setClearColor(bool clearColor_);
    /// Centers the mouse in the window
    void centerMouse();
private:
    void clear();
    void drawPixels();
    void drawAALine(double x1, double y1, Pixel* target);
    int width, height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Cursor* cursor;
    std::vector<Pixel>* pixels;
    bool clearing, autoDelete, renderLine, antialias, blendmode, clearColor;
    Uint8 clearRed, clearGreen, clearBlue;
};

#endif

