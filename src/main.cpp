#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include "display/Window.h"
#include "positioning/Point.h"
#include "positioning/Particle.h"

using namespace std;

int main(int argc, char** argv) {
    
    enum {RAINBOW, GRAYSCALE, REDSCALE, GREENSCALE, BLUESCALE};
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;
    Window window;
    bool done = false;
    bool mouseDown = false;
    bool renderWithLines = false;
    int mouseX = 0, mouseY = 0;
    int colormode = RAINBOW;
    
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
                        std::cout << "Line rendering: " << renderWithLines << "\n";
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
                    /* All color modes are set using the number keys. */
                    case SDLK_0:
                        colormode = RAINBOW;
                        std::cout << "Colormode: rainbow\n";
                        break;
                    case SDLK_1:
                        colormode = GRAYSCALE;
                        std::cout << "Colormode: grayscale\n";
                        break;
                    case SDLK_2:
                        colormode = REDSCALE;
                        std::cout << "Colormode: redscale\n";
                        break;
                    case SDLK_3:
                        colormode = GREENSCALE;
                        std::cout << "Colormode: greenscale\n";
                        break;
                    case SDLK_4:
                        colormode = BLUESCALE;
                        std::cout << "Colormode: bluescale\n";
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
            /* These points are used to define the three pixels. These are simply their initial kinetic properties. */
            Point pos(mouseX, mouseY);
            Point vel((double)std::rand()/RAND_MAX-0.5, (double)std::rand()/RAND_MAX-0.5);
            Point acc((double)std::rand()/RAND_MAX-0.5, (double)std::rand()/RAND_MAX-0.5);
            Point jer((double)std::rand()/RAND_MAX-0.5, (double)std::rand()/RAND_MAX-0.5);
            /* Construct the pixels with kinetic properties. */
            Pixel pixel1(pos, vel);
            Pixel pixel2(pos, vel, acc);
            Pixel pixel3(pos, vel, acc, jer);
            /* Certain color modes require constant, but random colors.  These are those RGB. */
            int temp1 = std::rand()%256;
            int temp2 = std::rand()%256;
            int temp3 = std::rand()%256;
            /* Sets the color of the pixels based on the colormode. */
            switch (colormode) {
                case RAINBOW:
                    pixel1.setColor(std::rand()%256, std::rand()%256, std::rand()%256);
                    pixel2.setColor(std::rand()%256, std::rand()%256, std::rand()%256);
                    pixel3.setColor(std::rand()%256, std::rand()%256, std::rand()%256);
                    break;
                case GRAYSCALE:
                    pixel1.setColor(temp1, temp1, temp1);
                    pixel2.setColor(temp2, temp2, temp2);
                    pixel3.setColor(temp3, temp3, temp3);
                    break;
                case REDSCALE:
                    pixel1.setColor(std::rand()%256, 0, 0);
                    pixel2.setColor(std::rand()%256, 0, 0);
                    pixel3.setColor(std::rand()%256, 0, 0);
                    break;
                case GREENSCALE:
                    pixel1.setColor(0, std::rand()%256, 0);
                    pixel2.setColor(0, std::rand()%256, 0);
                    pixel3.setColor(0, std::rand()%256, 0);
                    break;
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

