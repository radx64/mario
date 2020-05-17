#include "Main.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include <SDL2/SDL.h>

#include "AnimatedSprite.hpp"
#include "Camera.hpp"
#include "core/Audio.hpp"
#include "core/FpsCounter.hpp"
#include "core/Timer.hpp"
#include "LevelLoader.hpp"
#include "Sprite.hpp"
#include "TextRenderer.hpp"
#include "World.hpp"


#include "character/player/Player.hpp"
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

Main::Main(): width_(640), height_(480)
{

}

Main::~Main()
{
    delete sprites_;

    for (Object* object : gameObjects_)
    {
        delete object;
    }

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Main::initBitmapsContainter()
{
    std::string rootPath = "img/";

    sprites_ = new SpritesContainer(
    {
        { SpriteType::BRICK_RED,            rootPath + "environment/brickred.bmp"},
        { SpriteType::COIN_PARTICLE_0,      rootPath + "environment/coin_particle_0.bmp"},
        { SpriteType::COIN_PARTICLE_1,      rootPath + "environment/coin_particle_1.bmp"},
        { SpriteType::COIN_PARTICLE_2,      rootPath + "environment/coin_particle_2.bmp"},
        { SpriteType::COIN_PARTICLE_3,      rootPath + "environment/coin_particle_3.bmp"},
        { SpriteType::EXPLOSION_1,          rootPath + "particles/explosion1.bmp"},
        { SpriteType::EXPLOSION_2,          rootPath + "particles/explosion2.bmp"},
        { SpriteType::EXPLOSION_3,          rootPath + "particles/explosion3.bmp"},
        { SpriteType::FIREBALL_1,           rootPath + "particles/fireball1.bmp"},
        { SpriteType::FIREBALL_2,           rootPath + "particles/fireball2.bmp"},
        { SpriteType::FIREBALL_3,           rootPath + "particles/fireball3.bmp"},
        { SpriteType::FIREBALL_4,           rootPath + "particles/fireball4.bmp"},
        { SpriteType::GROUND_RED,           rootPath + "environment/gnd_red_1.bmp"},
        { SpriteType::MARIO_SMALL_JUMPING,  rootPath + "characters/mario/jump0.bmp"},
        { SpriteType::MARIO_SMALL_RUNNING_0,rootPath + "characters/mario/move0_0.bmp"},
        { SpriteType::MARIO_SMALL_RUNNING_1,rootPath + "characters/mario/move0_1.bmp"},
        { SpriteType::MARIO_SMALL_RUNNING_2,rootPath + "characters/mario/move0_2.bmp"},
        { SpriteType::MARIO_SMALL_SLIDING,  rootPath + "characters/mario/sliding0.bmp"},
        { SpriteType::MARIO_SMALL_STANDING, rootPath + "characters/mario/standing0.bmp"},
        { SpriteType::MARIO_BIG_CROUCHING,  rootPath + "characters/mario/crouch1.bmp"},
        { SpriteType::MARIO_BIG_JUMPING,    rootPath + "characters/mario/jump1.bmp"},
        { SpriteType::MARIO_BIG_RUNNING_0,  rootPath + "characters/mario/move1_0.bmp"},
        { SpriteType::MARIO_BIG_RUNNING_1,  rootPath + "characters/mario/move1_1.bmp"},
        { SpriteType::MARIO_BIG_RUNNING_2,  rootPath + "characters/mario/move1_2.bmp"},
        { SpriteType::MARIO_BIG_STANDING,   rootPath + "characters/mario/standing1.bmp"},
        { SpriteType::MARIO_BIG_SLIDING,    rootPath + "characters/mario/sliding1.bmp"},
        { SpriteType::MUSHROOM,             rootPath + "environment/mushroom.bmp"},
        { SpriteType::SQUID_0,              rootPath + "characters/squid/move0.bmp"},
        { SpriteType::SQUID_1,              rootPath + "characters/squid/move1.bmp"},
        { SpriteType::QUESTIONBLOCK_0,      rootPath + "environment/blockq_0.bmp"},
        { SpriteType::QUESTIONBLOCK_1,      rootPath + "environment/blockq_1.bmp"},
        { SpriteType::QUESTIONBLOCK_2,      rootPath + "environment/blockq_2.bmp"},
        { SpriteType::QUESTIONBLOCK_USED,   rootPath + "environment/blockq_used.bmp"},
        { SpriteType::BUSH_LEFT,            rootPath + "environment/bush_left.bmp"},
        { SpriteType::BUSH_MIDDLE,          rootPath + "environment/bush_middle.bmp"},
        { SpriteType::BUSH_RIGHT,           rootPath + "environment/bush_right.bmp"},
        { SpriteType::HILL_LEFT,            rootPath + "environment/hill_left.bmp"},
        { SpriteType::HILL_MIDDLE,          rootPath + "environment/hill_middle.bmp"},
        { SpriteType::HILL_MIDDLE_2,        rootPath + "environment/hill_middle_2.bmp"},
        { SpriteType::HILL_MIDDLE_3,        rootPath + "environment/hill_middle_3.bmp"},
        { SpriteType::HILL_RIGHT,           rootPath + "environment/hill_right.bmp"},
        { SpriteType::HILL_TOP,             rootPath + "environment/hill_top.bmp"},
        { SpriteType::GOOMBA_WALK_0,        rootPath + "characters/goomba/walk0.bmp"},
        { SpriteType::GOOMBA_WALK_1,        rootPath + "characters/goomba/walk1.bmp"},
        { SpriteType::GOOMBA_SQUASHED,      rootPath + "characters/goomba/squashed.bmp"},
        { SpriteType::PIPE_TOP_LEFT,        rootPath + "environment/pipe_top_left.bmp"},
        { SpriteType::PIPE_TOP_RIGHT,       rootPath + "environment/pipe_top_right.bmp"},
        { SpriteType::PIPE_BOTTOM_LEFT,     rootPath + "environment/pipe_bottom_left.bmp"},
        { SpriteType::PIPE_BOTTOM_RIGHT,    rootPath + "environment/pipe_bottom_right.bmp"},
        { SpriteType::SMALL_BRICK_1,        rootPath + "environment/small_brick_1.bmp"},
        { SpriteType::SMALL_BRICK_2,        rootPath + "environment/small_brick_2.bmp"}

    }
    );
    Context::setSprites(sprites_);
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

    //SDL_MaximizeWindow(window_);
    
    //SDL_SetWindowFullscreen(window_, 1);

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderTarget(renderer_, NULL);
    Context::setSdlRenderer(renderer_);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(renderer_, width_/2, height_/2);
    //SDL_RenderSetScale(renderer_, 2.5f, 2.5f);

    graphics::StillRenderer* stillRenderer = new graphics::StillRenderer();
    Context::setStillRenderer(stillRenderer);

    Camera* camera = new Camera();
    camera->setW(width_);
    camera->setH(height_);
    Context::setCamera(camera);

    core::Audio* audio = new core::Audio();
    Context::setAudio(audio);

    graphics::CameraRenderer* cameraRenderer = new graphics::CameraRenderer(camera);
    Context::setCameraRenderer(cameraRenderer);

    core::FpsCounter* fps = new core::FpsCounter();
    Context::setFpsCounter(fps);
    TextRenderer* text = new TextRenderer();
    Context::setTextRenderer(text);
    Context::setKeyboardState(&keys_);
    world_.lives_ = 99;
    Context::setWorld(&world_);

    initBitmapsContainter();
}


void update_key_state(const SDL_Event& event, const int keycode, bool& target)
{
    if (event.key.keysym.sym == keycode)
    {
        if (event.type == SDL_KEYDOWN) target = true;
        if (event.type == SDL_KEYUP) target = false;
    }
}

bool is_key_pressed_once(const int keycode, const SDL_Event& event)
{
    return (event.key.keysym.sym == keycode) && (event.type == SDL_KEYDOWN) && (event.key.repeat == 0);
}

void Main::key_handler(const SDL_Event& event)
{
    if (is_key_pressed_once(SDLK_p, event)) Context::getWorld()->paused_ = !Context::getWorld()->paused_;
    if (is_key_pressed_once(SDLK_BACKQUOTE, event)) debug_ = !debug_;
    if (is_key_pressed_once(SDLK_1, event)) { desiredFPS_ -= 10.0; if (desiredFPS_ < 20.0) desiredFPS_ = 20.0;}
    if (is_key_pressed_once(SDLK_2, event)) { desiredFPS_ += 10.0;}
    if (is_key_pressed_once(SDLK_q, event)) { running_ = false;}

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
        update_key_state(event, SDLK_UP, keys_.up);
        update_key_state(event, SDLK_DOWN, keys_.down);
        update_key_state(event, SDLK_LEFT, keys_.left);
        update_key_state(event, SDLK_RIGHT, keys_.right);
        update_key_state(event, SDLK_z, keys_.fire);
        update_key_state(event, SDLK_LSHIFT, keys_.run);
        update_key_state(event, SDLK_RETURN, keys_.enter);
    }
}

void Main::input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        key_handler(event);
        if (event.type == SDL_QUIT)
        {
            running_ = false;
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
    world_.level = LevelLoader::load("levels/0-0.lvl");

    character::player::Player* object = new character::player::Player();
    object->position = {64, 200};

    world_.level.backObjects.push_back(object);
    player_ = object;
}

void update(std::vector<Object*>& objects, std::vector<Object*>& allObjects, double dt)
{
    std::vector<Object*>::iterator it;

    if(Context::getWorld()->paused_) return;

    for (it = objects.begin(); it != objects.end(); ++it)
    {
        (*it)->simulate(dt);
    };

    for (it = objects.begin(); it != objects.end(); ++it)
    {
        /* Need optimize that (double loop with diferent ranges later to check collisions once not twice)*/
        (*it)->collide(allObjects);
    };

    for (it = objects.begin(); it != objects.end(); )
    {
        if ((*it)->dead_)
        {
            it = objects.erase(it);
        }
        else
        {
            ++it;
        }
    };
}

void spawn(std::vector<Object*>& objects, std::vector<Object*>& toSpawn)
{
    if (toSpawn.size() > 0)
    {

        for (auto objectToSpawn : toSpawn)
        {
            objects.push_back(objectToSpawn);
        }
        toSpawn.clear();
    }    
}

void draw(std::vector<Object*>& objects, double delta_time)
{
    for(Object* o : objects) o->draw(delta_time);
}

void Main::step(double delta_time)
{
    core::Timer profiler;
    profiler.start();

    /* awfull solution */
    std::vector<Object*> allObjects;
    allObjects.insert(allObjects.end(), world_.level.backObjects.begin(), world_.level.backObjects.end());
    allObjects.insert(allObjects.end(), world_.level.foreObjects.begin(), world_.level.foreObjects.end());

    update(world_.level.backObjects, allObjects, delta_time);
    update(world_.level.foreObjects, allObjects, delta_time);

    spawn(world_.level.backObjects, world_.level.toSpawnObjectsInBack);
    spawn(world_.level.foreObjects, world_.level.toSpawnObjectsInFore);

    player_->on_input();

    double physicsTime = profiler.getTicks();
    profiler.start();

    draw(world_.level.backObjects, delta_time);
    draw(world_.level.foreObjects, delta_time);
    double drawingTime = profiler.getTicks();

    int fps =  Context::getFpsCounter()->getLastMeasurement();
    auto text = Context::getTextRenderer();

    if (debug_)
    {
        text->draw(std::string("LMT: " + std::to_string((int)desiredFPS_)), width_/2 - 75, 20, 0.5);

        text->draw(std::string("PHY: " + std::to_string(physicsTime) + " ms"), width_/2 - 75, 28, 0.5);
        text->draw(std::string("DRW: " + std::to_string(drawingTime) + " ms"), width_/2 - 75, 36, 0.5);
        text->draw(std::string("SLP: " + std::to_string((int)frameFreezeTime_) + " ms"), width_/2 - 75, 44, 0.5);

        text->draw(std::string("PLAYER X: " + std::to_string(player_->position.x)), 10, 20, 0.5);
        text->draw(std::string("PLAYER Y: " + std::to_string(player_->position.y)), 10, 28, 0.5);
        text->draw(std::string("PLAYER VX: " + std::to_string(player_->velocity.x)), 10, 36, 0.5);
        text->draw(std::string("PLAYER VY: " + std::to_string(player_->velocity.y)), 10, 44, 0.5);

        text->draw(std::string("BACKOBJECTS: " + std::to_string(world_.level.backObjects.size())), 10, 52, 0.5);
        text->draw(std::string("FOREOBJECTS: " + std::to_string(world_.level.foreObjects.size())), 10, 60, 0.5);
    }
    
    auto world = Context::getWorld();

    text->draw(std::string("FPS: " + std::to_string(fps)), width_/2 - 75, 4, 1.0);
    text->draw(std::string("LIVES: " + std::to_string(world->lives_)), 25, 4, 1.0);
    text->draw(std::string("COINS: " + std::to_string(world->coins_)), 125, 4, 1.0);

    text->draw(std::string("dT: " + std::to_string(delta_time)), 125, 32, 0.5);
}

void Main::loop()
{
    initGameObjects();
    core::Timer frameTimer;
    //Context::getAudio()->playMusic();
    while (running_)
    {
        frameTimer.start();
        clear();
        input();
        step(simulationTimeStep_/1000.0f); // step in seconds

        SDL_RenderPresent(renderer_);
        frameFreezeTime_ = 1000.0 / desiredFPS_ - frameTimer.getTicks();
        frameFreezeTime_ = frameFreezeTime_ > 0 ? frameFreezeTime_ : 0.0;
        SDL_Delay(frameFreezeTime_ < 0 ? 0 : frameFreezeTime_);
        simulationTimeStep_ = frameTimer.getTicks();
        if (simulationTimeStep_ > 50.0)
        {
            simulationTimeStep_ = 50.0;
        /*         
          to much time step makes collision not work (flying through objects between frames)  
          to fixed that some raycasting or movement interpolation need to be done but I don't
          feel if it is needed. Less than 8 FPS is not playable and it causing problems only
          in those circumstances. So I'm ok with that in low FPS, simulation step will slow down
        */
        }

        Context::getFpsCounter()->measure();
        ++frame_;
    }
}
