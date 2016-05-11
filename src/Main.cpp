#include "Main.hpp"

#include <stdexcept>

Main::Main()
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
        throw(std::runtime_error(std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError()));
        return;
    }
    window_ = SDL_CreateWindow("Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    if (window_ == NULL)
    {
        throw(std::runtime_error(std::string("Window could not be created! SDL_Error: ") + SDL_GetError()));
        return;
    }

    surface_ = SDL_GetWindowSurface(window_);
    SDL_FillRect(surface_, NULL, SDL_MapRGB(surface_->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window_);
}


void Main::loop()
{
    SDL_Delay(5000); // fake 5 seconds loop for environment testing for now
}