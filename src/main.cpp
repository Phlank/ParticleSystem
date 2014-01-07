#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include "display/Window.h"
#include "positioning/Point.h"
#include "positioning/Particle.h"

using namespace std;

enum {RAINBOW, GRAYSCALE, REDSCALE, GREENSCALE, BLUESCALE};
enum {VEL, ACC, JER};

bool done;
bool mouseDown;
bool ctrl, alt, updown; /* Used for changing the scaling values. */
int mouseX, mouseY;
int colormode;
int scaleValue;
int numberOfPackets; /* The number of groups of particles generated with each frame. */

/* Used to scale the initial properties of the pixels. */
long double velScale;
long double accScale;
long double jerScale;
static const long double SCALE_CHANGE = 0.1;

/* Modifies the initial value scales. */
void modifyScale(bool ctrl_, bool alt_, bool updown_) {
    if (ctrl_) {
        if (updown_) accScale += SCALE_CHANGE;
        else accScale -= SCALE_CHANGE;
        std::cout << "Acceleration scale: " << accScale << "\n";
    } else if (alt_) {
        if (updown_) jerScale += SCALE_CHANGE;
        else jerScale -= SCALE_CHANGE;
        std::cout << "Jerk scale: " << jerScale << "\n";
    } else {
        if (updown_) velScale += SCALE_CHANGE;
        else velScale -= SCALE_CHANGE;
        std::cout << "Velocity scale: " << velScale << "\n";
    }
}

/* Main */
int main(int argc, char** argv) {
    
    /* SDL initialization. */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;
    Window window;
    
    /* Setting default values. */
    done = false;
    mouseDown = false;
    mouseX = mouseY = 0;
    colormode = RAINBOW;
    velScale = 1.0;
    accScale = 1.0;
    jerScale = 1.0;
    ctrl = alt = updown = false;
    numberOfPackets = 1;
    
    /* Main loop. */
    while (!done) {
        /* Poll for an event. */
        SDL_PollEvent(&event);
        /* Based on the event, do something. */
        switch (event.type) {
            /* Keydown events. */
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    /* Exits the program. */
                    case SDLK_q:
                        done = true;
                        std::cout << "Exiting\n";
                        break;
                    /* Toggle rendering line segments instead of singular points off and on. */
                    case SDLK_l:
                        if (window.getRenderLine()) window.setRenderLine(false);
                        else window.setRenderLine(true);
                        std::cout << "Line rendering: " << window.getRenderLine() << "\n";
                        break;
                    /* Toggle clearing the screen between each frame on and off. */
                    case SDLK_c:
                        if (window.getClearing()) window.setClearing(false);
                        else window.setClearing(true);
                        std::cout << "Window clearing: " << window.getClearing() << "\n";
                        break;
                    /* Dump the current pixels. */
                    case SDLK_d:
                        window.dump();
                        std::cout << "Particles dumped\n";
                        break;
                    /* Toggle automatic pixel deletion on and off. */
                    case SDLK_k:
                        if (window.getAutoDelete()) window.setAutoDelete(false);
                        else window.setAutoDelete(true);
                        std::cout << "Auto deletion: " << window.getAutoDelete() << "\n";
                        break;
                    /* Center the mouse in the window. */
                    case SDLK_f:
                        window.centerMouse();
                        break;
                    /* Toggle line antialiasing off and on. */
                    case SDLK_a:
                        if (window.getAntialias()) window.setAntialias(false);
                        else window.setAntialias(true);
                        std::cout << "Antialiasing: " << window.getAntialias() << "\n";
                        break;
                    /* Toggle the blend mode between blend and add. */
                    case SDLK_b:
                        if (window.getBlendMode()) window.setBlendMode(false);
                        else window.setBlendMode(true);
                        std::cout << "Blend mode: " << window.getBlendMode() << "\n";
                        break;
                    /* Toggle the background color between black and white. */
                    case SDLK_m:
                        if (window.getClearColor()) window.setClearColor(false);
                        else window.setClearColor(true);
                        std::cout << "Clearing color: " << window.getClearColor() << "\n";
                        break;
                    /* Used to modify the initial acceleration. */
                    case SDLK_LCTRL:
                        ctrl = true;
                        break;
                    /* Used to modify the initial jerk. */
                    case SDLK_LALT:
                        alt = true;
                        break;
                    /* Raise the initial velocity, acceleration, or jerk by an amount of SCALE_CHANGE. */
                    case SDLK_UP:
                        updown = true;
                        modifyScale(ctrl, alt, updown);
                        break;
                    /* Lower the initial velocity, acceleration, or jerk by an amount of SCALE_CHANGE. */
                    case SDLK_DOWN:
                        updown = false;
                        modifyScale(ctrl, alt, updown);
                        break;
                    /* Increase the number of packets of particles released per frame. */
                    case SDLK_RIGHT:
                        numberOfPackets++;
                        cout << "Number of packets: " << numberOfPackets << "\n";
                        break;
                    /* Decrease the number of packets of particles released per frame. */
                    case SDLK_LEFT:
                        if (numberOfPackets != 1) numberOfPackets--;
                        cout << "Number of packets: " << numberOfPackets << "\n";
                        break;
                    /* Set the value of */
                    /* All color modes are set using the number keys. */
                    /* Sets the color mode to rainbow. */
                    case SDLK_0:
                        colormode = RAINBOW;
                        std::cout << "Colormode: rainbow\n";
                        break;
                    /* Sets the color mode to rainbow. */
                    case SDLK_1:
                        colormode = GRAYSCALE;
                        std::cout << "Colormode: grayscale\n";
                        break;
                    /* Sets the color mode to redscale. */
                    case SDLK_2:
                        colormode = REDSCALE;
                        std::cout << "Colormode: redscale\n";
                        break;
                    /* Sets the color mode to greenscale. */
                    case SDLK_3:
                        colormode = GREENSCALE;
                        std::cout << "Colormode: greenscale\n";
                        break;
                    /* Sets the color mode to bluescale. */
                    case SDLK_4:
                        colormode = BLUESCALE;
                        std::cout << "Colormode: bluescale\n";
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_LCTRL:
                        ctrl = false;
                        break;
                    case SDLK_LALT:
                        alt = false;
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
        
        /* Makes new pixels if the mouse is pressed down. */
        if (mouseDown) {
            int i;
            for (i = 0; i < numberOfPackets; i++) {
                /* These points are used to define the three pixels. These are simply their initial kinetic properties. */
                Point pos(mouseX, mouseY);
                Point vel(((double) std::rand()/RAND_MAX-0.5)*velScale, ((double) std::rand()/RAND_MAX-0.5)*velScale);
                Point acc(((double) std::rand()/RAND_MAX-0.5)*accScale, ((double) std::rand()/RAND_MAX-0.5)*accScale);
                Point jer(((double) std::rand()/RAND_MAX-0.5)*jerScale, ((double) std::rand()/RAND_MAX-0.5)*jerScale);
                /* Construct the pixels with kinetic properties. */
                Pixel pixel1(pos, vel);
                Pixel pixel2(pos, vel, acc);
                Pixel pixel3(pos, vel, acc, jer);
                /* Certain color modes require constant colors. */
                uint8_t temp1;
                uint8_t temp2;
                uint8_t temp3;
                /* Sets the color of the pixels based on the colormode. */
                switch (colormode) {
                    /* Pixels have random RGB values. */
                    case RAINBOW:
                        pixel1.setColor(std::rand()%256, std::rand()%256, std::rand()%256);
                        pixel2.setColor(std::rand()%256, std::rand()%256, std::rand()%256);
                        pixel3.setColor(std::rand()%256, std::rand()%256, std::rand()%256);
                        break;
                    /* Pixels have locally consistent random RGB values. */
                    case GRAYSCALE:
                        temp1 = std::rand()%256;
                        temp2 = std::rand()%256;
                        temp3 = std::rand()%256;
                        pixel1.setColor(temp1, temp1, temp1);
                        pixel2.setColor(temp2, temp2, temp2);
                        pixel3.setColor(temp3, temp3, temp3);
                        break;
                    /* Pixels have a random R value, and GB equal zero. */
                    case REDSCALE:
                        pixel1.setColor(std::rand()%256, 0, 0);
                        pixel2.setColor(std::rand()%256, 0, 0);
                        pixel3.setColor(std::rand()%256, 0, 0);
                        break;
                    /* Pixels have a random G value, and RB equal zero. */
                    case GREENSCALE:
                        pixel1.setColor(0, std::rand()%256, 0);
                        pixel2.setColor(0, std::rand()%256, 0);
                        pixel3.setColor(0, std::rand()%256, 0);
                        break;
                    /* Pixels have a random B value, and RG equal zero. */
                    case BLUESCALE:
                        pixel1.setColor(0, 0, std::rand()%256);
                        pixel2.setColor(0, 0, std::rand()%256);
                        pixel3.setColor(0, 0, std::rand()%256);
                        break;
                    default:
                        break;
                }
                /* Add the pixels to the window. */
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

