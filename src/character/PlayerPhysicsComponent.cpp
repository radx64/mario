#include "PlayerPhysicsComponent.hpp"

#include <cmath>
#include <iostream>

#include "Camera.hpp"
#include "Context.hpp"
#include "Player.hpp"
#include "KeyboardState.hpp"
#include "World.hpp"

#include <SDL2/SDL.h>

namespace character
{

PlayerPhysicsComponent::PlayerPhysicsComponent(Player& player)
: player_(player)
{}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{}

void PlayerPhysicsComponent::bouceOfCeiling(Object* ceilingBlock)
{
    if (player_.ay < 0.0)
    {
        player_.ay = 0;
        player_.y += player_.ay;
        player_.y = ceilingBlock->y + ceilingBlock->h;
    }
}

bool PlayerPhysicsComponent::isObjectAt(std::vector<Object*> gameObjects, float x, float y)
{
    for(auto object : gameObjects)
    {
        if ((x >= object->x && x < object->x + object->w) &&
            (y >= object->y && y < object->y + object->h) &&
            (object != &player_))
        {
            return true;
        }
    }
    return false;
}

void PlayerPhysicsComponent::simulate()
{
    auto keys = Context::getKeyboardState();

    player_.ay += grav_;
    player_.x += player_.ax;
    player_.y += player_.ay;

    Context::getCamera()->setX(player_.x);
    Context::getCamera()->setY(player_.y);

    if (fabs(player_.ax) > 1.0) player_.state = Player::State::Running;
    else player_.state = Player::State::Standing;

    if (keys->up)
    {
        if (!player_.jumped_)
        {
            player_.ay = -8.0;
            player_.jumped_ = true;
        }
        else
        {
            player_.ay -= 0.04;
        }
    }
    else
    {
       player_.ay += 0.2;
    }


    if (keys->left)
    {
        player_.ax += -0.6;
        if (player_.ax > 0) player_.state = Player::State::Sliding;
    }

    if (keys->right)
    {
        player_.ax += 0.6;
        if (player_.ax < 0) player_.state = Player::State::Sliding;
    }

    if (player_.ax > horizontalMaxSpeed_) player_.ax = horizontalMaxSpeed_;
    if (player_.ax < -horizontalMaxSpeed_) player_.ax = -horizontalMaxSpeed_;

    if (player_.jumped_) player_.state = Player::State::Jumping;

    if (!keys->left && !keys->right) player_.ax *= 0.65;


    int playerXRendererPosition = (int)player_.x - Context::getCamera()->getX();
    int playerYRendererPosition = (int)player_.y - Context::getCamera()->getY();

    auto renderer = Context::getSdlRenderer();
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xAA, 0x77);
    SDL_Rect r{
        playerXRendererPosition, 
        playerYRendererPosition, 
        (int)player_.w, 
        (int)player_.h};
    SDL_RenderDrawRect(renderer, &r);

    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<4; ++j)
        {
            if (isObjectAt(
                Context::getWorld()->level.gameObjects,
                player_.x+ (i-1)*32+16,
                player_.y+ (j-1)*32+16))
            {
                SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x77);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xAA, 0x77); 
            }



            r = SDL_Rect{
                playerXRendererPosition + (i-1)*32, 
                playerYRendererPosition + (j-1)*32, 
                32, 
                32};
            SDL_RenderDrawRect(renderer, &r);
        }
    }





}

void PlayerPhysicsComponent::onCollisionWith(Collision collision, Object& object)
{
    if (collision.get() == Collision::State::Left)
    {

         if (player_.ax < 0) player_.ax = 0;
         if (object.x + object.w > player_.x) player_.x = object.x + player_.w;
    }

    if (collision.get() == Collision::State::Right)
    {
        if (player_.ax > 0) player_.ax = 0;
        if (player_.x + player_.w < object.x ) player_.x = object.x - player_.w;
    }

    if (collision.get() == Collision::State::Bottom)
    {
        player_.y = object.y - player_.h;
        if (player_.ay > 0) player_.ay = 0;
        player_.jumped_ = false;
    }

    if (collision.get() == Collision::State::Top)
    {
    /**
        Below is special behaviour for future Mario development
        When Mario is jumping up and hit obstacle with his head
        He slides a bit to be next to the block (to jump on block above him)
        instead of just bouncing down
    **/
        bouceOfCeiling(&object);

        if ( player_.x + player_.w - object.x < 10.0f)
        {
            // if (!isObjectAt(gameObjects, object.x - player_.w, object.y))
            // {
            //     player_.x = object.x - player_.w;
            // }
            // else
            // {
                bouceOfCeiling(&object);
            // }
        }

        else if(object.x + object.w - player_.x < 10.0f)
        {
            // if (!isObjectAt(gameObjects, object.x + object.w , object.y))
            // {
            //     player_.x = object.x + player_.w;
            // }
            // else
            // {
                bouceOfCeiling(&object);
            // }
        }
        else
        {
            bouceOfCeiling(&object);
        }
    }
}

}  // namespace character
