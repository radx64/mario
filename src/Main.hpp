#ifndef MAIN_HPP_
#define MAIN_WINDOW_HPP_

#include "SDL2/SDL.h"

class Main
{
public:
    Main();
    ~Main();
    void init();
    void loop();

private:
    SDL_Window* window_;
    SDL_Surface* surface_;
};

#endif  // MAIN_HPP_ 
