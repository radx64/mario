#include "Main.hpp"

#include <stdexcept>
#include <cmath>

#include <SDL2/SDL.h>

#include "Bitmap.hpp"
#include "TextRenderer.hpp"

#include <iostream>

Main::Main(): width_(800), height_(600)
{ }

Main::~Main()
{
    SDL_DestroyRenderer(renderer_);
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

void Main::input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            running_ = false;
        }
        else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            bool isKeyDown = (event.type == SDL_KEYDOWN);

            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    keys_.up = isKeyDown;
                    break;
                case SDLK_DOWN:
                    keys_.down = isKeyDown;
                    break;
                case SDLK_LEFT:
                    keys_.left = isKeyDown;
                    break;
                case SDLK_RIGHT:
                    keys_.right = isKeyDown;
                    break;
                case SDLK_SPACE:
                    keys_.jump = isKeyDown;
                    break;
                case SDLK_LSHIFT:
                    keys_.run = isKeyDown;
                    break;
                case SDLK_RETURN:
                    keys_.enter = isKeyDown;
                    break;
            }
        }
    }
}


void Main::loop()
{
    Bitmap mario(renderer_, "../img/mario_jump.bmp");
    Bitmap ground(renderer_, "../img/gnd_red_1.bmp");
    TextRenderer text(renderer_);

    running_ = true;
    int frame = 0;
    int marioCount = 7;

    while (running_)
    {
        input();
        if (keys_.up) ++marioCount;
        if (keys_.down) --marioCount;
        SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF); 
        SDL_RenderClear(renderer_);
        SDL_SetRenderDrawColor(renderer_, marioCount*10, 0x00, 0xFF, 0xFF);        
        SDL_RenderDrawLine(renderer_, 0, height_ / 2, width_, height_ / 2);
        for (int i = 0; i < marioCount; ++i)
        {
            mario.draw(i*(100 * 8.0/marioCount), height_/2 + 100 - fabs(sin(i+frame/10.0)) * 90.0f);
        }

        for (int j = 0; j < 5; ++j)
        {
            for (int i = 0; i < 25; ++i)
            {
                ground.draw(i*32, 450+j*32);
            }
        }
        text.setColor(0x55, 0x55, 0x55);
        text.draw(std::string("Frame: " + std::to_string(frame)), 11, 21);
        text.setColor(0xFF, 0xFF, 0xFF);
        text.draw(std::string("Frame: " + std::to_string(frame)), 10, 20);
        SDL_RenderPresent(renderer_);
        SDL_Delay(10);

        ++frame;
    }
}
