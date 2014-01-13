#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include "display/Window.h"
#include "positioning/Point.h"
#include "positioning/Particle.h"

using namespace std;

enum {RAINBOW, GRAYSCALE, REDSCALE, GREENSCALE, BLUESCALE, PURPLESCALE, ORANGESCALE, YELLOWSCALE, CYANSCALE};
enum {VEL, ACC, JER};

bool done;
bool mouseDown, autoGeneration, makeNewPixels;
bool ctrlPressed, altPressed, upOrDown;
int mouseX, mouseY;
int newPixelX, newPixelY;
int colormode;
int scaleValue;
int numberOfPackets;
int halfWidth, halfHeight;
Window window;

/* Used to scale the initial properties of the pixels. */
long double velScale;
long double accScale;
long double jerScale;
static const long double SCALE_CHANGE = 0.1;

/* Sets the colors for a pixel packet */
void setPixelColors(Pixel* p1, Pixel* p2, Pixel* p3) {
    int temp1, temp2, temp3;
    switch (colormode) {
        /* Pixels have random RGB values. */
        case RAINBOW:
            p1->setColor(std::rand()%256, std::rand()%256, std::rand()%256);
            p2->setColor(std::rand()%256, std::rand()%256, std::rand()%256);
            p3->setColor(std::rand()%256, std::rand()%256, std::rand()%256);
            break;
        /* Pixels have locally consistent random RGB values. */
        case GRAYSCALE:
            temp1 = std::rand()%256;
            temp2 = std::rand()%256;
            temp3 = std::rand()%256;
            p1->setColor(temp1, temp1, temp1);
            p2->setColor(temp2, temp2, temp2);
            p3->setColor(temp3, temp3, temp3);
            break;
        /* Pixels have a random R value, and GB equal zero. */
        case REDSCALE:
            p1->setColor(std::rand()%256, 0, 0);
            p2->setColor(std::rand()%256, 0, 0);
            p3->setColor(std::rand()%256, 0, 0);
            break;
        /* Pixels have a random G value, and RB equal zero. */
        case GREENSCALE:
            p1->setColor(0, std::rand()%256, 0);
            p2->setColor(0, std::rand()%256, 0);
            p3->setColor(0, std::rand()%256, 0);
            break;
        /* Pixels have a random B value, and RG equal zero. */
        case BLUESCALE:
            p1->setColor(0, 0, std::rand()%256);
            p2->setColor(0, 0, std::rand()%256);
            p3->setColor(0, 0, std::rand()%256);
            break;
        /* Pixels have a random B value, R is half of B, and G is zero. */
        case PURPLESCALE:
            temp1 = std::rand()%256;
            temp2 = std::rand()%256;
            temp3 = std::rand()%256;
            p1->setColor(temp1/2, 0, temp1);
            p2->setColor(temp2/2, 0, temp2);
            p3->setColor(temp3/2, 0, temp3);
            break;
        /* G is half of R, B is zero. */
        case ORANGESCALE:
            temp1 = std::rand()%256;
            temp2 = std::rand()%256;
            temp3 = std::rand()%256;
            p1->setColor(temp1, temp1/2, 0);
            p2->setColor(temp2, temp2/2, 0);
            p3->setColor(temp3, temp3/2, 0);
            break;
        /* R = G, B = 0. */
        case YELLOWSCALE:
            temp1 = std::rand()%256;
            temp2 = std::rand()%256;
            temp3 = std::rand()%256;
            p1->setColor(temp1, temp1, 0);
            p2->setColor(temp2, temp2, 0);
            p3->setColor(temp3, temp3, 0);
            break;
        /* RG = B/2 */
        case CYANSCALE:
            temp1 = std::rand()%256;
            temp2 = std::rand()%256;
            temp3 = std::rand()%256;
            p1->setColor(temp1/2, temp1/2, temp1);
            p2->setColor(temp2/2, temp2/2, temp2);
            p3->setColor(temp3/2, temp3/2, temp3);
        default:
            break;
    }
}

void modifyScale(bool ctrl_, bool alt_, bool updown_) {
    if (ctrl_) {
        if (updown_) accScale += SCALE_CHANGE;
        else if (accScale > 0.0) accScale -= SCALE_CHANGE;
    } else if (alt_) {
        if (updown_) jerScale += SCALE_CHANGE;
        else if (jerScale > 0.0) jerScale -= SCALE_CHANGE;
    } else {
        if (updown_) velScale += SCALE_CHANGE;
        else if (velScale > 0.0) velScale -= SCALE_CHANGE;
    }
}
void toggleLineRendering() {
    if (window.getRenderLine()) window.setRenderLine(false);
    else window.setRenderLine(true);
}
void toggleScreenClearing() {
    if (window.getClearing()) window.setClearing(false);
    else window.setClearing(true);
}
void toggleAutomaticDumping() {
    if (window.getAutoDelete()) window.setAutoDelete(false);
    else window.setAutoDelete(true);
}
void toggleLineAntialiasing() {
    if (window.getAntialias()) window.setAntialias(false);
    else window.setAntialias(true);
}
void toggleBlendMode() {
    if (window.getBlendMode() == 0) window.setBlendMode(1);
    else if (window.getBlendMode() == 1) window.setBlendMode(2);
    else window.setBlendMode(0);
}
void toggleClearingColor() {
    if (window.getClearColor()) window.setClearColor(false);
    else window.setClearColor(true);
}
void toggleAutomaticGeneration() {
    if (autoGeneration) { autoGeneration = false; window.setCursorVisible(true); }
    else { autoGeneration = true; window.setCursorVisible(false); }
}
/* Processes possible events */
void processEvents(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_q:
                    done = true;
                    break;
                case SDLK_l:
                    toggleLineRendering();
                    break;
                case SDLK_c:
                    toggleScreenClearing();
                    break;
                case SDLK_d:
                    window.dump();
                    break;
                case SDLK_k:
                    toggleAutomaticDumping();
                    break;
                case SDLK_f:
                    window.centerMouse();
                    break;
                case SDLK_a:
                    toggleLineAntialiasing();
                    break;
                case SDLK_b:
                    toggleBlendMode();
                    break;
                case SDLK_m:
                    toggleClearingColor();
                    break;
                case SDLK_LCTRL:
                    ctrlPressed = true;
                    break;
                case SDLK_LALT:
                    altPressed = true;
                    break;
                case SDLK_UP:
                    upOrDown = true;
                    modifyScale(ctrlPressed, altPressed, upOrDown);
                    break;
                case SDLK_DOWN:
                    upOrDown = false;
                    modifyScale(ctrlPressed, altPressed, upOrDown);
                    break;
                case SDLK_RIGHT:
                    numberOfPackets++;
                    break;
                case SDLK_LEFT:
                    if (numberOfPackets != 1) numberOfPackets--;
                    break;
                case SDLK_SPACE:
                    toggleAutomaticGeneration();
                    break;
                case SDLK_0:
                    colormode = RAINBOW;
                    break;
                case SDLK_1:
                    colormode = GRAYSCALE;
                    break;
                case SDLK_2:
                    colormode = REDSCALE;
                    break;
                case SDLK_3:
                    colormode = GREENSCALE;
                    break;
                case SDLK_4:
                    colormode = BLUESCALE;
                    break;
                case SDLK_5:
                    colormode = PURPLESCALE;
                    break;
                case SDLK_6:
                    colormode = ORANGESCALE;
                    break;
                case SDLK_7:
                    colormode = YELLOWSCALE;
                    break;
                case SDLK_8:
                    colormode = CYANSCALE;
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_LCTRL:
                    ctrlPressed = false;
                    break;
                case SDLK_LALT:
                    altPressed = false;
                    break;
                default:
                    break;
            }
            break;
        /* Mouse button down events. */
        case SDL_MOUSEBUTTONDOWN:
            mouseDown = true;
            mouseX = event.button.x;
            mouseY = event.button.y;
            break;
        /* Mouse button up events. */
        case SDL_MOUSEBUTTONUP:
            mouseDown = false;
            break;
        /* Mouse motion events. */
        case SDL_MOUSEMOTION:
            mouseX = event.motion.x;
            mouseY = event.motion.y;
            break;
        default:
            break;
    } /* End of event processing */
}

/* Add n pixel packets to the window */
void addPixelPackets(int n) {
    int i;
    for (i = 0; i < n; i++) {
        /* These points are used to define the three pixels. These are simply their initial kinetic properties. */
        Point pos(mouseX, mouseY);
        Point vel(((double) std::rand()/RAND_MAX-0.5)*velScale, ((double) std::rand()/RAND_MAX-0.5)*velScale);
        Point acc(((double) std::rand()/RAND_MAX-0.5)*accScale, ((double) std::rand()/RAND_MAX-0.5)*accScale);
        Point jer(((double) std::rand()/RAND_MAX-0.5)*jerScale, ((double) std::rand()/RAND_MAX-0.5)*jerScale);
        /* Define the three pixels of a pixel packet */
        Pixel pixel1(pos, vel);
        Pixel pixel2(pos, vel, acc);
        Pixel pixel3(pos, vel, acc, jer);
        /* Set the color of the pixels */
        setPixelColors(&pixel1, &pixel2, &pixel3);
        /* Add the pixels to the window */
        window.addPixel(pixel1);
        window.addPixel(pixel2);
        window.addPixel(pixel3);
    }
}

/* Main */
int main(int argc, char** argv) {
    
    /* SDL initialization. */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;
    window = Window();
    
    /* Setting default values. */
    done = false;
    mouseDown = false;
    autoGeneration = false;
    mouseX = mouseY = 0;
    colormode = RAINBOW;
    velScale = 1.0;
    accScale = 1.0;
    jerScale = 1.0;
    ctrlPressed = altPressed = upOrDown = false;
    numberOfPackets = 1;
    halfWidth = window.getWidth()/2;
    halfHeight = window.getHeight()/2;
    
    /* Main loop. */
    while (!done) {
        /* Poll for an event. */
        SDL_PollEvent(&event);
        /* Process the event */
        processEvents(event);
        
        makeNewPixels = mouseDown || autoGeneration; //Condition to be met to make more pixels
        
        if (makeNewPixels) {
            if (mouseDown) { newPixelX = mouseX; newPixelY = mouseY; }
            else { newPixelX = halfWidth; newPixelY = halfHeight; }
            addPixelPackets(numberOfPackets);
        }
        
        /* Delay for framerate, then draw the window. */
        SDL_Delay(5);   //When this line is not present, the program encounters large delays when drawing.
        window.draw();
    }
    
    //Cleanup
    window.~Window();
    SDL_Quit();
    
    //Exit program
    return 0;
}

