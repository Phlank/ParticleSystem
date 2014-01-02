#ifndef PIXEL_H
#define	PIXEL_H

#include <stdint.h>
#include "../positioning/Particle.h"

using namespace std;

static const uint8_t DEF_RED = 0;
static const uint8_t DEF_GREEN = 0;
static const uint8_t DEF_BLUE = 0;
static const uint8_t DEF_OPACITY = 255;

class Pixel : public Particle {
public:
    Pixel();
    Pixel(Point pos_);
    Pixel(Point pos_, Point vel_);
    Pixel(Point pos_, Point vel_, Point acc_);
    Pixel(Point pos_, Point vel_, Point acc_, Point jer_);
    Pixel(int red_, int green_, int blue_);
    Pixel(int red_, int green_, int blue_, int opacity_);
    Pixel(int red_, int green_, int blue_, Point pos_);
    Pixel(int red_, int green_, int blue_, int opacity_, Point pos_);
    Pixel(int red_, int green_, int blue_, Point pos_, Point vel_);
    Pixel(int red_, int green_, int blue_, int opacity_, Point pos_, Point vel_);
    Pixel(int red_, int green_, int blue_, Point pos_, Point vel_, Point acc_);
    Pixel(int red_, int green_, int blue_, int opacity_, Point pos_, Point vel_, Point acc_);
    Pixel(int red_, int green_, int blue_, Point pos_, Point vel_, Point acc_, Point jer_);
    Pixel(int red_, int green_, int blue_, int opacity_, Point pos_, Point vel_, Point acc_, Point jer_);
    Pixel(const Pixel& orig);
    virtual ~Pixel();
    uint8_t getRed();
    uint8_t getGreen();
    uint8_t getBlue();
    uint8_t getOpacity();
    void setColor(int red_, int green_, int blue_);
    void setColor(int red_, int green_, int blue_, int opacity_);
private:
    uint8_t red, green, blue, opacity;
};

#endif

