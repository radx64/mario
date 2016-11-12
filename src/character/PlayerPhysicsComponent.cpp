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
    if (player_.velocity.y < 0.0)
    {
        player_.velocity.y = 0;
        player_.position.y += player_.velocity.y;
        player_.position.y = ceilingBlock->position.y + ceilingBlock->size.y;
    }
}

bool PlayerPhysicsComponent::isObjectAt(std::vector<Object*> gameObjects, float x, float y)
{
    for(auto object : gameObjects)
    {
        if ((x >= object->position.x && x < object->position.x + object->size.x) &&
            (y >= object->position.y && y < object->position.y + object->size.y) &&
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

    player_.velocity.y += grav_;
    player_.position.x += player_.velocity.x;
    player_.position.y += player_.velocity.y;

    Context::getCamera()->setX(player_.position.x);
    Context::getCamera()->setY(player_.position.y);

    if (fabs(player_.velocity.x) > 1.0) player_.state = Player::State::Running;
    else player_.state = Player::State::Standing;

    if (keys->up)
    {
        if (!player_.jumped_)
        {
            player_.velocity.y = -8.0;
            player_.jumped_ = true;
        }
        else
        {
            player_.velocity.y -= 0.04;
        }
    }
    else
    {
       player_.velocity.y += 0.2;
    }


    if (keys->left)
    {
        player_.velocity.x += -0.6;
        if (player_.velocity.x > 0) player_.state = Player::State::Sliding;
    }

    if (keys->right)
    {
        player_.velocity.x += 0.6;
        if (player_.velocity.x < 0) player_.state = Player::State::Sliding;
    }

    if (player_.velocity.x > horizontalMaxSpeed_) player_.velocity.x = horizontalMaxSpeed_;
    if (player_.velocity.x < -horizontalMaxSpeed_) player_.velocity.x = -horizontalMaxSpeed_;

    if (player_.jumped_) player_.state = Player::State::Jumping;

    if (!keys->left && !keys->right) player_.velocity.x *= 0.65;
}

void PlayerPhysicsComponent::onCollisionWith(Collision collision, Object& object)
{
    std::cout << "Collision at x:" << object.position.x << " y:" << object.position.y << std::endl; 



    if (collision.get() == Collision::State::Bottom)
    {
        player_.position.y = object.position.y - player_.size.y;
        if (player_.velocity.y > 0) player_.velocity.y = 0;
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

        if ( player_.position.x + player_.size.x - object.position.x < 10.0f)
        {
            // if (!isObjectAt(gameObjects, object.position.x - player_.size.x, object.y))
            // {
            //     player_.position.x = object.position.x - player_.size.x;
            // }
            // else
            // {
                bouceOfCeiling(&object);
            // }
        }

        else if(object.position.x + object.size.x - player_.position.x < 10.0f)
        {
            // if (!isObjectAt(gameObjects, object.position.x + object.size.x , object.y))
            // {
            //     player_.position.x = object.position.x + player_.size.x;
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

    if (collision.get() == Collision::State::Left)
    {

         if (player_.velocity.x < 0) player_.velocity.x = 0;
         if (object.position.x + object.size.x > player_.position.x) player_.position.x = object.position.x + player_.size.x;
    }

    if (collision.get() == Collision::State::Right)
    {
        if (player_.velocity.x > 0) player_.velocity.x = 0;
        if (player_.position.x + player_.size.x < object.position.x ) player_.position.x = object.position.x - player_.size.x;
    }



}

}  // namespace character
