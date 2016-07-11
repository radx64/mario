#include "Main.hpp"

#include <stdexcept>
#include <cmath>

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "Bitmap.hpp"
#include "FpsCounter.hpp"
#include "TextRenderer.hpp"
#include "Timer.hpp"

#include "character/Player.hpp"
#include "environment/BrickBlock.hpp"

#include <iostream>
#include <iomanip>

/**
                        IMPORTANT NOTICE:
Please take into consideration that current implementation of Main class is
"a mine field" done only to design and test in field rest of project components.

If it ugly, hacky and and makes You cry, it should be done that way :).

**/

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

    context_.setRenderer(renderer_);

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
       { BitmapType::SQUID_0,         rootPath + "characters/squid/move0.bmp"},
       { BitmapType::SQUID_1,         rootPath + "characters/squid/move1.bmp"},
       { BitmapType::QUESTIONBLOCK_0, rootPath + "blockq_0.bmp"},
       { BitmapType::QUESTIONBLOCK_1, rootPath + "blockq_1.bmp"},
       { BitmapType::QUESTIONBLOCK_2, rootPath + "blockq_2.bmp"}
    }
    );
    context_.setBitmapsContainer(bitmaps_);
    FpsCounter* fps = new FpsCounter();
    context_.setFpsCounter(fps);
    TextRenderer* text = new TextRenderer(renderer_);
    context_.setTextRenderer(text);
    context_.setKeyboardState(&keys_);
    frame_ = 0;
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

void Main::initGameObjects()
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


    Object* debugObject = new character::Player(context_, 0);
        debugObject->x = 200;
        debugObject->y = 0;

    gameObjects_.push_back(debugObject);

    debugObject = new environment::BrickBlock(context_, 1);
        debugObject->x = 500;
        debugObject->y = 40;
        debugObject->w = 32;
        debugObject->h = 32;

    gameObjects_.push_back(debugObject);

    for (int i = 2; i < 10; ++i)
    {
        Object* debugObject = new environment::BrickBlock(context_, i);
        debugObject->x = 100 + i * 32;
        debugObject->y = 100;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);
    }

    for (int i = 10; i < 20; ++i)
    {
        Object* debugObject = new environment::BrickBlock(context_, i);
        debugObject->x = 100 + i * 32;
        debugObject->y = 132;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);
    }

    for (int i = 3; i < 26; ++i)
    {
        Object* debugObject = new environment::BrickBlock(context_, i);
        debugObject->x = (i-1) * 32;
        debugObject->y = 300;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);
    }

     for (int i = 1; i < 10; ++i)
    {
        Object* debugObject = new environment::BrickBlock(context_, i);
        debugObject->x = (i-1) * 32;
        debugObject->y = 200;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);
    }

    for (int i = 0; i < 25; ++i)
    {
        Object* debugObject = new environment::BrickBlock(context_, i*10);
        debugObject->x = i * 32;
        debugObject->y = 450;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);
    }

        debugObject = new environment::BrickBlock(context_, 90);
        debugObject->x = 0;
        debugObject->y = 386;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);


    // remember to destroy objects above when done, duh...
}


void Main::simpleScene()
{
    if(sin(frame_/10.0) > 0)
    {
        bitmaps_->get(BitmapType::MARIO_JUMPING)->draw(
            width_/2,
            height_/2 + 100 - (sin(frame_/10.0)) * 90.0f);
    }
    else
    {
        bitmaps_->get(BitmapType::MARIO_STANDING)->draw(
        width_/2,
        height_/2 + 88);
    }
    bitmaps_->get(BitmapType::MARIO_STANDING)->draw(width_/2 - 32*4, 136);

    runningMario_->draw(frame_*3 % width_, 386);

    questionBlock_->draw(width_/2 - 32*4, 200);
    questionBlock_->draw(width_/2 + 32*4, 200);

    questionBlock_->draw(width_/2, 280);

    int fps =  context_.getFpsCounter()->getLastMeasurement();
    auto text = context_.getTextRenderer();
    text->draw(std::string("FPS: " + std::to_string(fps)), width_ - 150, 4, 2.0);
    text->draw(std::string("frame_:  " + std::to_string(frame_)), 10, 4, 2.0);

    for (unsigned int index = 0; index < gameObjects_.size(); ++index)
    {
        Object* obj = gameObjects_[index];
        obj->simulate(gameObjects_);
        obj->draw();
    }

    if (gameObjects_.front()->x > width_) gameObjects_.front()->x = 0;
    if (gameObjects_.front()->x < 0) gameObjects_.front()->x = width_;

    if (gameObjects_.front()->y > height_) gameObjects_.front()->y = 0;


    questionBlock_->nextFrame();
    runningMario_->nextFrame();
}

void Main::loop()
{
    const float desiredFPS = 60.0;
    initGameObjects();
    running_ = true;
    Timer frameTimer;

    while (running_)
    {
        frameTimer.start();
        clear();
        input();
        simpleScene();
        SDL_RenderPresent(renderer_);

        double frameFreezeTime = 1000.0 / desiredFPS - frameTimer.getTicks();

        SDL_Delay(frameFreezeTime<0?0:frameFreezeTime);
        context_.getFpsCounter()->measure();
        ++frame_;
    }
}
