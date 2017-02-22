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
    (void) ceilingBlock;
    if (player_.velocity.y < 0.0)
    {
        player_.velocity.y *= -1.0;
    }
}

void PlayerPhysicsComponent::simulate()
{
    auto keys = Context::getKeyboardState();

    player_.velocity.y += grav_;

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
        player_.velocity.x -= 0.6;
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

    player_.position.x += player_.velocity.x;
    player_.position.y += player_.velocity.y;
}

void PlayerPhysicsComponent::onCollisionWith(Collision collision, Object& object)
{
    if (collision.get() == Collision::State::Bottom)
    {
        player_.position.y = object.position.y - player_.size.y;
        if (player_.velocity.y > 0) player_.velocity.y = 0;
        player_.jumped_ = false;
    }

    if (collision.get() == Collision::State::Top)
    {
        bouceOfCeiling(&object);
    }

    if (collision.get() == Collision::State::Left)
    {
        player_.velocity.x = 0;
        player_.position.x = object.position.x + object.size.x;
    }

    if (collision.get() == Collision::State::Right)
    {
        player_.velocity.x = 0;
        player_.position.x = object.position.x - player_.size.x ;
    }

}

}  // namespace character
