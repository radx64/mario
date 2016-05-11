#include "Main.hpp"

#include <stdexcept>
#include <cmath>

#include <SDL2/SDL.h>

#include "Bitmap.hpp"

Main::Main(): width_(640), height_(480)
{ }

Main::~Main()
{
    SDL_DestroyWindow(window_);
    SDL_Quit();  
}

void Main::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw(std::runtime_error(
            std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError()));
        return;
    }
    window_ = SDL_CreateWindow("Mario", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        width_, 
        height_, 
        SDL_WINDOW_SHOWN);

    if (window_ == nullptr)
    {
        throw(std::runtime_error(
            std::string("Window could not be created! SDL_Error: ") + SDL_GetError()));
        return;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
}

void Main::loop()
{
    for (int frame = 0; frame < 500; ++frame)
    {
        SDL_RenderClear(renderer_);
        Bitmap b(renderer_, "../img/mario.bmp");
        for (int i = 0; i < 15; ++i)
        {
            b.draw(renderer_, i*50, height_/2 + sin(i+frame/10.0) * 50.0f);
        }
        SDL_RenderPresent(renderer_);
        SDL_Delay(5); // fake 5 seconds loop for environment testing for now
    }
}
