#include "Pixel.h"

Pixel::Pixel() : Particle() {
    red = DEFAULT_RED;
    green = DEFAULT_GREEN;
    blue = DEFAULT_BLUE;
    opacity = DEFAULT_OPACITY;
}

Pixel::Pixel(Point pos_) : Particle(pos_) {
    red = DEFAULT_RED;
    green = DEFAULT_GREEN;
    blue = DEFAULT_BLUE;
    opacity = DEFAULT_OPACITY;
}

Pixel::Pixel(Point pos_, Point vel_) : Particle(pos_, vel_) {
    red = DEFAULT_RED;
    green = DEFAULT_GREEN;
    blue = DEFAULT_BLUE;
    opacity = DEFAULT_OPACITY;
}

Pixel::Pixel(Point pos_, Point vel_, Point acc_) : Particle(pos_, vel_, acc_) {
    red = DEFAULT_RED;
    green = DEFAULT_GREEN;
    blue = DEFAULT_BLUE;
    opacity = DEFAULT_OPACITY;
}

Pixel::Pixel(Point pos_, Point vel_, Point acc_, Point jer_) : Particle(pos_, vel_, acc_, jer_) {
    red = DEFAULT_RED;
    green = DEFAULT_GREEN;
    blue = DEFAULT_BLUE;
    opacity = DEFAULT_OPACITY;
}

Pixel::Pixel(int red_, int green_, int blue_) : Particle() {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = DEFAULT_OPACITY;
}

Pixel::Pixel(int red_, int green_, int blue_, int opacity_) : Particle() {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = opacity_;
}

Pixel::Pixel(int red_, int green_, int blue_, Point pos_) : Particle(pos_) {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = DEFAULT_OPACITY;
}

Pixel::Pixel(int red_, int green_, int blue_, int opacity_, Point pos_) : Particle(pos_) {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = opacity_;
}

Pixel::Pixel(int red_, int green_, int blue_, Point pos_, Point vel_) : Particle(pos_, vel_) {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = DEFAULT_OPACITY;
}

Pixel::Pixel(int red_, int green_, int blue_, int opacity_, Point pos_, Point vel_) : Particle(pos_, vel_) {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = opacity_;
}

Pixel::Pixel(int red_, int green_, int blue_, Point pos_, Point vel_, Point acc_) : Particle(pos_, vel_, acc_) {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = DEFAULT_OPACITY;
}

Pixel::Pixel(int red_, int green_, int blue_, int opacity_, Point pos_, Point vel_, Point acc_) : Particle(pos_, vel_, acc_) {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = opacity_;
}

Pixel::Pixel(int red_, int green_, int blue_, Point pos_, Point vel_, Point acc_, Point jer_) : Particle(pos_, vel_, acc_, jer_) {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = DEFAULT_OPACITY;
}

Pixel::Pixel(int red_, int green_, int blue_, int opacity_, Point pos_, Point vel_, Point acc_, Point jer_) : Particle(pos_, vel_, acc_, jer_) {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = opacity_;
}

Pixel::Pixel(const Pixel& orig) : Particle(orig) {
    red = orig.red;
    green = orig.green;
    blue = orig.blue;
    opacity = orig.opacity;
}

Pixel::~Pixel() {
    
}

uint8_t Pixel::getRed() {
    return red;
}

uint8_t Pixel::getGreen() {
    return green;
}

uint8_t Pixel::getBlue() {
    return blue;
}

uint8_t Pixel::getOpacity() {
    return opacity;
}

void Pixel::setColor(int red_, int green_, int blue_) {
    red = red_;
    green = green_;
    blue = blue_;
}

void Pixel::setColor(int red_, int green_, int blue_, int opacity_) {
    red = red_;
    green = green_;
    blue = blue_;
    opacity = opacity_;
}

bool Pixel::runPixelFrame() {
    bool output = this->runFrame();
    setColor(red, green, blue, 255/DEFAULT_LIFE*this->getLife());
    return output;
}

