#ifndef PIXEL_H
#define	PIXEL_H

#include <stdint.h>
#include "../positioning/Particle.h"

static const uint8_t DEFAULT_RED = 0;
static const uint8_t DEFAULT_GREEN = 0;
static const uint8_t DEFAULT_BLUE = 0;
static const uint8_t DEFAULT_OPACITY = 255;
static const bool DEFAULT_RENDER_LINE_MODE = false;

class Pixel : public Particle {
public:
    /// Creates a new pixel with default values.
    Pixel();
    /// Creates a new pixel with the given position.
    Pixel(Point pos_);
    /// Creates a new pixel with position and one derivative.
    Pixel(Point pos_, Point vel_);
    /// Creates a new pixel with position and two derivatives.
    Pixel(Point pos_, Point vel_, Point acc_);
    /// Creates a new pixel with position and three derivatives.
    Pixel(Point pos_, Point vel_, Point acc_, Point jer_);
    /// Creates a new pixel with RGB values.
    Pixel(int red_, int green_, int blue_);
    /// Creates a new pixel with RGB values with opacity.
    Pixel(int red_, int green_, int blue_, int opacity_);
    /// Creates a new pixel with RGB values and position.
    Pixel(int red_, int green_, int blue_, Point pos_);
    /// Creates a new pixel with RGB values with opacity and position.
    Pixel(int red_, int green_, int blue_, int opacity_, Point pos_);
    /// Creates a new pixel with RGB values and position with one derivative.
    Pixel(int red_, int green_, int blue_, Point pos_, Point vel_);
    /// Creates a new pixel with RGB values with opacity and position with one derivative.
    Pixel(int red_, int green_, int blue_, int opacity_, Point pos_, Point vel_);
    /// Creates a new pixel with RGB values and position with two derivatives.
    Pixel(int red_, int green_, int blue_, Point pos_, Point vel_, Point acc_);
    /// Creates a new pixel with RGB values with opacity and position with two derivatives.
    Pixel(int red_, int green_, int blue_, int opacity_, Point pos_, Point vel_, Point acc_);
    /// Creates a new pixel with RGB values and position with three derivatives.
    Pixel(int red_, int green_, int blue_, Point pos_, Point vel_, Point acc_, Point jer_);
    /// Creates a new pixel with RGB values with opacity and position with three derivatives.
    Pixel(int red_, int green_, int blue_, int opacity_, Point pos_, Point vel_, Point acc_, Point jer_);
    /// Creates a new pixel from an existing one.
    Pixel(const Pixel& orig);
    /// Class destructor.
    virtual ~Pixel();
    /// \return the red value of this pixel
    uint8_t getRed();
    /// \return the green value of this pixel
    uint8_t getGreen();
    /// \return the blue value of this pixel
    uint8_t getBlue();
    /// \return the opacity value of this pixel
    uint8_t getOpacity();
    /// \return the rendering mode of this pixel
    /// false - renders points; true - renders line segments
    bool getRenderLineMode();
    /// Sets the RGB values of this pixel.
    void setColor(int red_, int green_, int blue_);
    /// Sets the RGB values and opacity of this pixel.
    void setColor(int red_, int green_, int blue_, int opacity_);
    /// Sets the rendering mode of this pixel.
    /// false - renders points; true - renders line segments
    void setRenderLineMode(bool renderLines_);
private:
    uint8_t red, green, blue, opacity;
    bool renderLines;
};

#endif

