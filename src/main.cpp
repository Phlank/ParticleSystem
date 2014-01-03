#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include "display/Window.h"
#include "positioning/Point.h"
#include "positioning/Particle.h"

using namespace std;

int main(int argc, char** argv) {
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event event;
    Window window;
    bool done = false;
    bool mouseDown = false;
    bool renderWithLines = false;
    int mouseX, mouseY;
    
    while (!done) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        done = true;
                        break;
                    case SDLK_l:
                        if (renderWithLines) renderWithLines = false;
                        else renderWithLines = true;
                        break;
                    case SDLK_c:
                        if (window.getClearing()) window.setClearing(false);
                        else window.setClearing(true);
                        break;
                    case SDLK_d:
                        window.dump();
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseDown = true;
                mouseX = event.button.x;
                mouseY = event.button.y;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseDown = false;
                break;
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                break;
            default:
                break;
        }
        if (mouseDown) {
            Point pos(mouseX, mouseY);
            Point vel((double)std::rand()/RAND_MAX-0.5, (double)std::rand()/RAND_MAX-0.5);
            Point acc((double)std::rand()/RAND_MAX-0.5, (double)std::rand()/RAND_MAX-0.5);
            Point jer((double)std::rand()/RAND_MAX-0.5, (double)std::rand()/RAND_MAX-0.5);
            Pixel pixel2(std::rand()%256, std::rand()%256, std::rand()%256, pos, vel);
            Pixel pixel3(std::rand()%256, std::rand()%256, std::rand()%256, pos, vel, acc);
            Pixel pixel4(std::rand()%256, std::rand()%256, std::rand()%256, pos, vel, acc, jer);
            if (renderWithLines) {
                pixel2.setRenderLineMode(true);
                pixel3.setRenderLineMode(true);
                pixel4.setRenderLineMode(true);
            }
            window.addPixel(pixel2); window.addPixel(pixel3); window.addPixel(pixel4);
        }
        window.draw();
    }
    
    window.~Window();
    SDL_Quit();
    return 0;
}

