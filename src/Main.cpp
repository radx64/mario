#include "Main.hpp"

#include <stdexcept>
#include <cmath>

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "Bitmap.hpp"
#include "Camera.hpp"
#include "FpsCounter.hpp"
#include "LevelLoader.hpp"
#include "TextRenderer.hpp"
#include "Timer.hpp"
#include "World.hpp"


#include "character/Player.hpp"
#include "environment/BrickBlock.hpp"
#include "environment/CoinBlock.hpp"
#include "environment/GroundBlock.hpp"
#include "graphics/StillRenderer.hpp"
#include "graphics/CameraRenderer.hpp"

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

    bitmaps_ = new BitmapsContainer(
    {
        { BitmapType::BRICK_RED,            rootPath + "environment/brickred.bmp" },
        { BitmapType::GROUND_RED,           rootPath + "environment/gnd_red_1.bmp"},
        { BitmapType::MARIO_JUMPING,        rootPath + "characters/mario/jump.bmp"},
        { BitmapType::MARIO_RUNNING_0,      rootPath + "characters/mario/move0.bmp"},
        { BitmapType::MARIO_RUNNING_1,      rootPath + "characters/mario/move1.bmp"},
        { BitmapType::MARIO_RUNNING_2,      rootPath + "characters/mario/move2.bmp"},
        { BitmapType::MARIO_STANDING,       rootPath + "characters/mario/standing.bmp"},
        { BitmapType::MARIO_SLIDING,        rootPath + "characters/mario/sliding.bmp"},
        { BitmapType::SQUID_0,              rootPath + "characters/squid/move0.bmp"},
        { BitmapType::SQUID_1,              rootPath + "characters/squid/move1.bmp"},
        { BitmapType::QUESTIONBLOCK_0,      rootPath + "environment/blockq_0.bmp"},
        { BitmapType::QUESTIONBLOCK_1,      rootPath + "environment/blockq_1.bmp"},
        { BitmapType::QUESTIONBLOCK_2,      rootPath + "environment/blockq_2.bmp"},
        { BitmapType::BUSH_LEFT,            rootPath + "environment/bush_left.bmp"},
        { BitmapType::BUSH_MIDDLE,          rootPath + "environment/bush_middle.bmp"},
        { BitmapType::BUSH_RIGHT,           rootPath + "environment/bush_right.bmp"},
        { BitmapType::HILL_LEFT,            rootPath + "environment/hill_left.bmp"},
        { BitmapType::HILL_MIDDLE,          rootPath + "environment/hill_middle.bmp"},
        { BitmapType::HILL_MIDDLE_2,        rootPath + "environment/hill_middle_2.bmp"},
        { BitmapType::HILL_MIDDLE_3,        rootPath + "environment/hill_middle_3.bmp"},
        { BitmapType::HILL_RIGHT,           rootPath + "environment/hill_right.bmp"},
        { BitmapType::HILL_TOP,             rootPath + "environment/hill_top.bmp"},
        { BitmapType::PIPE_TOP_LEFT,        rootPath + "environment/pipe_top_left.bmp"},
        { BitmapType::PIPE_TOP_RIGHT,       rootPath + "environment/pipe_top_right.bmp"},
        { BitmapType::PIPE_BOTTOM_LEFT,     rootPath + "environment/pipe_bottom_left.bmp"},
        { BitmapType::PIPE_BOTTOM_RIGHT,    rootPath + "environment/pipe_bottom_right.bmp"},

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
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL |  SDL_WINDOW_RESIZABLE);

    if (window_ == nullptr)
    {
        throw(std::runtime_error(
            std::string("Window could not be created! SDL_Error: ") + SDL_GetError()));
        return;
    }

    SDL_SetWindowFullscreen(window_, 0);

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderTarget(renderer_, NULL);
    Context::setSdlRenderer(renderer_);

    graphics::StillRenderer* stillRenderer = new graphics::StillRenderer();
    Context::setStillRenderer(stillRenderer);

    Camera* camera = new Camera();
    camera->setW(width_);
    camera->setH(height_);
    Context::setCamera(camera);

    graphics::CameraRenderer* cameraRenderer = new graphics::CameraRenderer(camera);
    Context::setCameraRenderer(cameraRenderer);

    FpsCounter* fps = new FpsCounter();
    Context::setFpsCounter(fps);
    TextRenderer* text = new TextRenderer();
    Context::setTextRenderer(text);
    Context::setKeyboardState(&keys_);
    frame_ = 0;
    world_.lives_ = 3;
    Context::setWorld(&world_);


    initBitmapsContainter();
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
    auto objects = LevelLoader::load("../levels/0-0.lvl");
    world_.level = LevelLoader::load("../levels/0-0.lvl");

    Object* object = new character::Player(0);
    object->x = 256;
    object->y = 128;

    world_.level.gameObjects.push_back(object);
    // remember to destroy objects above when done, duh...
}


void Main::simpleScene()
{
    for (auto const& object : world_.level.backgroundObjects)
    {
        object->update(std::vector<Object*>{});
    }

    for (auto const& object : world_.level.gameObjects)
    {
        object->update(world_.level.gameObjects);
    }
    int fps =  Context::getFpsCounter()->getLastMeasurement();
    auto text = Context::getTextRenderer();
    text->draw(std::string("FPS: " + std::to_string(fps)), width_ - 150, 4, 2.0);
    text->draw(std::string("frame :  " + std::to_string(frame_)), 10, 4, 2.0);

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
        SDL_Delay(frameFreezeTime < 0 ? 0 : frameFreezeTime);
        Context::getFpsCounter()->measure();
        ++frame_;
    }
}
