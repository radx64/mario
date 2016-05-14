#include "Main.hpp"

#include <stdexcept>
#include <cmath>

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "Bitmap.hpp"
#include "FpsCounter.hpp"
#include "TextRenderer.hpp"
#include "Timer.hpp"

#include <iostream>

Main::Main(): width_(800), height_(600)
{ 


}

Main::~Main()
{
    delete runningMario_;
    delete questionBlock_;
    delete bitmaps_;

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

    //SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderTarget(renderer_, NULL);

    std::string rootPath = "../img/";

    bitmaps_ = new BitmapsContainer(renderer_,
    {
       { BitmapType::BRICK_RED,       rootPath + "brickred.bmp" },
       { BitmapType::GROUND_RED,      rootPath + "gnd_red_1.bmp"},
       { BitmapType::MARIO_JUMPING,   rootPath + "characters/mario/jump.bmp"},
       { BitmapType::MARIO_RUNNING_0, rootPath + "characters/mario/move0.bmp"},
       { BitmapType::MARIO_RUNNING_1, rootPath + "characters/mario/move1.bmp"},
       { BitmapType::MARIO_RUNNING_2, rootPath + "characters/mario/move2.bmp"},
       { BitmapType::MARIO_STANDING,  rootPath + "characters/mario/standing.bmp"},
       { BitmapType::QUESTIONBLOCK_0, rootPath + "blockq_0.bmp"},
       { BitmapType::QUESTIONBLOCK_1, rootPath + "blockq_1.bmp"},
       { BitmapType::QUESTIONBLOCK_2, rootPath + "blockq_2.bmp"}
    }
    );
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

void Main::clear()
{
    SDL_SetRenderDrawColor(renderer_, 92, 148, 252, 0xFF); 
    SDL_RenderClear(renderer_);    
}

void Main::simpleScene(TextRenderer& text, int& frame, FpsCounter& fps)
{
    bitmaps_->get(BitmapType::MARIO_JUMPING)->draw(
        width_/2, 
        height_/2 + 100 - fabs(sin(frame/10.0)) * 90.0f);

    bitmaps_->get(BitmapType::MARIO_STANDING)->draw(width_/2 - 32*4, 136);

    runningMario_->draw(frame*3 % width_, 386);

    questionBlock_->draw(width_/2 - 32*4, 200);
    questionBlock_->draw(width_/2 + 32*4, 200);

    for (int j = 0; j < 5; ++j)
    {
        for (int i = 0; i < 25; ++i)
        {
            bitmaps_->get(BitmapType::GROUND_RED)->draw(i*32, 450+j*32);
        }
    }

    for (int i = 0; i < 25; ++i)
    {
        bitmaps_->get(BitmapType::BRICK_RED)->draw(i*32, 280);
    }

    questionBlock_->draw(width_/2, 280);

    int a = 5; (void)a; (void)fps;
    std::string fspMeter = "FPS: " + std::to_string(int(fps.measure()));
    text.draw(fspMeter, width_ - 150, 4, 2.0);

    text.draw(std::string("Frame:  " + std::to_string(frame)), 10, 4, 2.0);
    SDL_RenderPresent(renderer_);
    SDL_Delay(10);
    questionBlock_->nextFrame();
    runningMario_->nextFrame();
    ++frame;    
}

void Main::loop()
{
    questionBlock_ = new AnimatedBitmap(
    {
        BitmapType::QUESTIONBLOCK_0, 
        BitmapType::QUESTIONBLOCK_2, 
        BitmapType::QUESTIONBLOCK_1,
        BitmapType::QUESTIONBLOCK_2
    }, 10, *bitmaps_);

    runningMario_ = new AnimatedBitmap(
    {
        BitmapType::MARIO_RUNNING_0,
        BitmapType::MARIO_RUNNING_1,
        BitmapType::MARIO_RUNNING_2
    }, 3, *bitmaps_);

    TextRenderer text(renderer_);

    running_ = true;
    int frame = 0;

    FpsCounter fps;
    while (running_)
    {
        clear();
        input();
        simpleScene(text, frame, fps);
    }
}
