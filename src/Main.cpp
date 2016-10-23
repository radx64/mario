#include "Main.hpp"

#include <stdexcept>
#include <cmath>

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "Bitmap.hpp"
#include "Camera.hpp"
#include "FpsCounter.hpp"
#include "TextRenderer.hpp"
#include "Timer.hpp"
#include "World.hpp"

#include "character/Player.hpp"
#include "environment/BrickBlock.hpp"
#include "environment/CoinBlock.hpp"
#include "environment/GroundBlock.hpp"

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
    delete bitmaps_;

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Main::initBitmapsContainter()
{
    std::string rootPath = "../img/";

    bitmaps_ = new BitmapsContainer(renderer_,
    {
       { BitmapType::BRICK_RED,       rootPath + "environment/brickred.bmp" },
       { BitmapType::GROUND_RED,      rootPath + "environment/gnd_red_1.bmp"},
       { BitmapType::MARIO_JUMPING,   rootPath + "characters/mario/jump.bmp"},
       { BitmapType::MARIO_RUNNING_0, rootPath + "characters/mario/move0.bmp"},
       { BitmapType::MARIO_RUNNING_1, rootPath + "characters/mario/move1.bmp"},
       { BitmapType::MARIO_RUNNING_2, rootPath + "characters/mario/move2.bmp"},
       { BitmapType::MARIO_STANDING,  rootPath + "characters/mario/standing.bmp"},
       { BitmapType::SQUID_0,         rootPath + "characters/squid/move0.bmp"},
       { BitmapType::SQUID_1,         rootPath + "characters/squid/move1.bmp"},
       { BitmapType::QUESTIONBLOCK_0, rootPath + "environment/blockq_0.bmp"},
       { BitmapType::QUESTIONBLOCK_1, rootPath + "environment/blockq_1.bmp"},
       { BitmapType::QUESTIONBLOCK_2, rootPath + "environment/blockq_2.bmp"}
    }
    );
    Context::setBitmapsContainer(bitmaps_);
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

    SDL_SetWindowFullscreen(window_, 0);

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderTarget(renderer_, NULL);
    initBitmapsContainter();
    Context::setRenderer(renderer_);
    FpsCounter* fps = new FpsCounter();
    Context::setFpsCounter(fps);
    TextRenderer* text = new TextRenderer(renderer_);
    Context::setTextRenderer(text);
    Context::setKeyboardState(&keys_);
    frame_ = 0;
    world_.lives_ = 3;
    Context::setWorld(&world_);

    Camera* camera = new Camera();
    Context::setCamera(camera);
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
    Object* debugObject = new character::Player(0);
        debugObject->x = 200;
        debugObject->y = 0;

    gameObjects_.push_back(debugObject);

    for (int i = 2; i < 10; ++i)
    {
        Object* debugObject = new environment::BrickBlock(i);
        debugObject->x = 100 + i * 32;
        debugObject->y = 100;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);
    }

    for (int i = 10; i < 20; ++i)
    {
        Object* debugObject = new environment::BrickBlock(i);
        debugObject->x = 100 + i * 32;
        debugObject->y = 132;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);
    }

    for (int i = 6; i < 26; ++i)
    {
        Object* debugObject = new environment::BrickBlock(i);
        debugObject->x = (i-1) * 32;
        debugObject->y = 350;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);
    }

     for (int i = 1; i < 10; ++i)
    {
        Object* debugObject = new environment::BrickBlock(i);
        debugObject->x = (i-1) * 32;
        debugObject->y = 200;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);
    }

    for (int i = 0; i < 10; ++i)
    {
        Object* debugObject = new environment::BrickBlock(i*10);
        debugObject->x = i * 32;
        debugObject->y = 450;
        debugObject->w = 32;
        debugObject->h = 32;

        gameObjects_.push_back(debugObject);
    }

    debugObject = new environment::BrickBlock(90);
    debugObject->x = 0;
    debugObject->y = 386;
    debugObject->w = 32;
    debugObject->h = 32;
    gameObjects_.push_back(debugObject);

    for (int j = 0; j < 2 ; ++j)
    {
        for (int i = 0; i < 50; ++i)
        {
            Object* debugObject = new environment::GroundBlock(i*10+j);
            debugObject->x = i * 32;
            debugObject->y = 550 + j*32;
            debugObject->w = 32;
            debugObject->h = 32;

            gameObjects_.push_back(debugObject);
        }
    }

    debugObject = new environment::CoinBlock(100);
    debugObject->x = 350;
    debugObject->y = 240;
    debugObject->w = 32;
    debugObject->h = 32;
    gameObjects_.push_back(debugObject);

    // remember to destroy objects above when done, duh...
}


void Main::simpleScene()
{
    for (unsigned int index = 0; index < gameObjects_.size(); ++index)
    {
        Object* obj = gameObjects_[index];
        obj->update(gameObjects_);
    }

    if (gameObjects_.front()->x > width_*2) gameObjects_.front()->x = 0;
    if (gameObjects_.front()->x < 0) gameObjects_.front()->x = width_*2;

    if (gameObjects_.front()->y > height_) gameObjects_.front()->y = 0;

    int fps =  Context::getFpsCounter()->getLastMeasurement();
    auto text = Context::getTextRenderer();
    text->draw(std::string("FPS: " + std::to_string(fps)), width_ - 150, 4, 2.0);
    text->draw(std::string("frame_:  " + std::to_string(frame_)), 10, 4, 2.0);

    auto world = Context::getWorld();

    text->draw(std::string("LIVES: " + std::to_string(world->lives_)), 250, 4, 2.0);
    text->draw(std::string("COINS: " + std::to_string(world->coins_)), 450, 4, 2.0);
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
        Context::getFpsCounter()->measure();
        ++frame_;
    }
}
