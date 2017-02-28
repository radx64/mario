#include "character/player/PhysicsComponent.hpp"

#include <cmath>

#include "Camera.hpp"
#include "Context.hpp"
#include "Player.hpp"
#include "KeyboardState.hpp"
#include "World.hpp"

namespace character
{
namespace player
{

PhysicsComponent::PhysicsComponent(Player& player)
: player_(player)
{}

inline void PhysicsComponent::bouceOfCeiling()
{
    if (player_.velocity.y < 0.0) player_.velocity.y *= -1.0;
}

inline void PhysicsComponent::jump()
{
    player_.velocity.y = -5.0;
    player_.jumped_ = true;
  
}

inline void PhysicsComponent::fall()
{
    player_.velocity.y += 0.05;   
}

inline void PhysicsComponent::moveLeft(float& horizontalAcceleration)
{
    horizontalAcceleration = -0.5;
    if (player_.velocity.x > 0) player_.state = Player::State::Sliding;
}

inline void PhysicsComponent::moveRight(float& horizontalAcceleration)
{
    horizontalAcceleration = 0.5;
    if (player_.velocity.x < 0) player_.state = Player::State::Sliding;
}

inline float PhysicsComponent::getMaxHorizontalSpeed(bool running)
{
    return running ? horizontalMaxSpeedRun_ : horizontalMaxSpeedWalk_;
}

void PhysicsComponent::simulate()
{
    auto keys = Context::getKeyboardState();

    player_.velocity.x *=0.91;

    player_.velocity.y += grav_;

    if (fabs(player_.velocity.x) > 0.1) player_.state = Player::State::Running;
    else player_.state = Player::State::Standing;

    if (keys->up)
    {
        if (!player_.jumped_)
        {
            jump();
        }
        else
        {
            player_.velocity.y -= 0.015;
        } 
    }
    else
    {
        fall();
    }

    float horizontalAcceleration{};

    if (keys->left) moveLeft(horizontalAcceleration);
    if (keys->right) moveRight(horizontalAcceleration);

    if (abs(player_.velocity.x) >= getMaxHorizontalSpeed(keys->run)) 
    {
            horizontalAcceleration *= 0.3f;
    }

    player_.velocity.x += horizontalAcceleration;

    player_.setAnimationSpeed((horizontalMaxSpeedRun_ + 1 - abs(player_.velocity.x )) * 2);

    if (player_.jumped_) player_.state = Player::State::Jumping;


    player_.position += player_.velocity;

    Context::getCamera()->setX(player_.position.x);
    Context::getCamera()->setY(player_.position.y);
}

void PhysicsComponent::onCollisionWith(Collision collision, Object& object)
{

    if (collision.get() == Collision::State::Bottom)
    {
        if (object.type_ == ObjectType::Enemy)
        {
            jump();
        }
        else
        {
            player_.position.y = object.position.y - player_.size.y;
            if (player_.velocity.y > 0) player_.velocity.y = 0;
            player_.jumped_ = false;
        }
    }

    if (collision.get() == Collision::State::Top)
    {
        bouceOfCeiling();
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

}  // namespace player
}  // namespace character
