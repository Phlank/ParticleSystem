#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include "display/Window.h"
#include "positioning/Point.h"
#include "positioning/Particle.h"

using namespace std;

enum {RAINBOW, GRAYSCALE, REDSCALE, GREENSCALE, BLUESCALE, PURPLESCALE, ORANGESCALE, YELLOWSCALE};
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
        default:
            break;
    }
}

/* Modifies the initial value scales. */
void modifyScale(bool ctrl_, bool alt_, bool updown_) {
    if (ctrl_) {
        if (updown_) accScale += SCALE_CHANGE;
        else accScale -= SCALE_CHANGE;
        //std::cout << "Acceleration scale: " << accScale << "\n";
    } else if (alt_) {
        if (updown_) jerScale += SCALE_CHANGE;
        else jerScale -= SCALE_CHANGE;
        //std::cout << "Jerk scale: " << jerScale << "\n";
    } else {
        if (updown_) velScale += SCALE_CHANGE;
        else velScale -= SCALE_CHANGE;
        //std::cout << "Velocity scale: " << velScale << "\n";
    }
}

/* Processes possible events */
void processEvents(SDL_Event event) {
    /* Based on the event, do something. */
    switch (event.type) {
        /* Keydown events. */
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                /* Exits the program. */
                case SDLK_q:
                    done = true;
                    //std::cout << "Exiting\n";
                    break;
                /* Toggle rendering line segments instead of singular points off and on. */
                case SDLK_l:
                    if (window.getRenderLine()) window.setRenderLine(false);
                    else window.setRenderLine(true);
                    //std::cout << "Line rendering: " << window.getRenderLine() << "\n";
                    break;
                /* Toggle clearing the screen between each frame on and off. */
                case SDLK_c:
                    if (window.getClearing()) window.setClearing(false);
                    else window.setClearing(true);
                    //std::cout << "Window clearing: " << window.getClearing() << "\n";
                    break;
                /* Dump the current pixels. */
                case SDLK_d:
                    window.dump();
                    //std::cout << "Particles dumped\n";
                    break;
                /* Toggle automatic pixel deletion on and off. */
                case SDLK_k:
                    if (window.getAutoDelete()) window.setAutoDelete(false);
                    else window.setAutoDelete(true);
                    //std::cout << "Auto deletion: " << window.getAutoDelete() << "\n";
                    break;
                /* Center the mouse in the window. */
                case SDLK_f:
                    window.centerMouse();
                    break;
                /* Toggle line antialiasing off and on. */
                case SDLK_a:
                    if (window.getAntialias()) window.setAntialias(false);
                    else window.setAntialias(true);
                    //std::cout << "Antialiasing: " << window.getAntialias() << "\n";
                    break;
                /* Toggle the blend mode between blend and add. */
                case SDLK_b:
                    if (window.getBlendMode() == 0) window.setBlendMode(1);
                    else if (window.getBlendMode() == 1) window.setBlendMode(2);
                    else window.setBlendMode(0);
                    //std::cout << "Blend mode: " << window.getBlendMode() << "\n";
                    break;
                /* Toggle the background color between black and white. */
                case SDLK_m:
                    if (window.getClearColor()) window.setClearColor(false);
                    else window.setClearColor(true);
                    //std::cout << "Clearing color: " << window.getClearColor() << "\n";
                    break;
                /* Used to modify the initial acceleration. */
                case SDLK_LCTRL:
                    ctrlPressed = true;
                    break;
                /* Used to modify the initial jerk. */
                case SDLK_LALT:
                    altPressed = true;
                    break;
                /* Raise the initial velocity, acceleration, or jerk by an amount of SCALE_CHANGE. */
                case SDLK_UP:
                    upOrDown = true;
                    modifyScale(ctrlPressed, altPressed, upOrDown);
                    break;
                /* Lower the initial velocity, acceleration, or jerk by an amount of SCALE_CHANGE. */
                case SDLK_DOWN:
                    upOrDown = false;
                    modifyScale(ctrlPressed, altPressed, upOrDown);
                    break;
                /* Increase the number of packets of particles released per frame. */
                case SDLK_RIGHT:
                    numberOfPackets++;
                   //std::cout << "Number of packets: " << numberOfPackets << "\n";
                    break;
                /* Decrease the number of packets of particles released per frame. */
                case SDLK_LEFT:
                    if (numberOfPackets != 1) numberOfPackets--;
                   //std::cout << "Number of packets: " << numberOfPackets << "\n";
                    break;
                /* Toggle automatic particle generation*/
                case SDLK_SPACE:
                    if (autoGeneration) { autoGeneration = false; window.setCursorVisible(true); }
                    else { autoGeneration = true; window.setCursorVisible(false); }
                    break;
                /* All color modes are set using the number keys. */
                /* Sets the color mode to rainbow. */
                case SDLK_0:
                    colormode = RAINBOW;
                    //std::cout << "Colormode: rainbow\n";
                    break;
                /* Sets the color mode to rainbow. */
                case SDLK_1:
                    colormode = GRAYSCALE;
                    //std::cout << "Colormode: grayscale\n";
                    break;
                /* Sets the color mode to redscale. */
                case SDLK_2:
                    colormode = REDSCALE;
                    //std::cout << "Colormode: redscale\n";
                    break;
                /* Sets the color mode to greenscale. */
                case SDLK_3:
                    colormode = GREENSCALE;
                    //std::cout << "Colormode: greenscale\n";
                    break;
                /* Sets the color mode to bluescale. */
                case SDLK_4:
                    colormode = BLUESCALE;
                    //std::cout << "Colormode: bluescale\n";
                    break;
                /* Sets the color mode to purplescale. */
                case SDLK_5:
                    colormode = PURPLESCALE;
                    //std::cout << "Colormode: purplescale\n";
                    break;
                /* Sets the color mode to orangescale. */
                case SDLK_6:
                    colormode = ORANGESCALE;
                    //std::cout << "Colormode: orangescale\n";
                    break;
                /* Sets the color mode to yellowscale. */
                case SDLK_7:
                    colormode = YELLOWSCALE;
                    //std::cout << "Colormode: yellowscale\n";
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
            int pixelPacketNumber = 0;
            /* Make pixel packets and add them to the window */
            for (pixelPacketNumber = 0; pixelPacketNumber < numberOfPackets; pixelPacketNumber++) {
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

