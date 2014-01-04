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
      
    while (!done) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        done = true;
                        std::cout << "Exiting\n";
                        break;
                    case SDLK_l:
                        if (window.getRenderLine()) window.setRenderLine(false);
                        else window.setRenderLine(true);
                        std::cout << "Line rendering: " << renderWithLines << "\n";
                        break;
                    case SDLK_c:
                        if (window.getClearing()) window.setClearing(false);
                        else window.setClearing(true);
                        std::cout << "Window clearing: " << window.getClearing() << "\n";
                        break;
                    case SDLK_d:
                        window.dump();
                        std::cout << "Particles dumped\n";
                        break;
                    case SDLK_k:
                        if (window.getAutoDelete()) window.setAutoDelete(false);
                        else window.setAutoDelete(true);
                        std::cout << "Auto deletion: " << window.getAutoDelete() << "\n";
                        break;
                    case SDLK_f:
                        window.centerMouse();
                        break;
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
            Pixel pixel1(pos, vel);
            Pixel pixel2(pos, vel, acc);
            Pixel pixel3(pos, vel, acc, jer);
            int temp1 = std::rand()%256;
            int temp2 = std::rand()%256;
            int temp3 = std::rand()%256;
            /* Constructs pixels based on the colormode. */
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
            window.addPixel(pixel1);
            window.addPixel(pixel2);
            window.addPixel(pixel3);
        }
        SDL_Delay(5);
        window.draw();
    }
    
    window.~Window();
    SDL_Quit();
    return 0;
}

