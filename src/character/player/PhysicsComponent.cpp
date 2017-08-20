#include "character/player/PhysicsComponent.hpp"

#include <cmath>

#include "Camera.hpp"
#include "Context.hpp"
#include "core/Audio.hpp"
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
    player_.velocity.y = -200.0;
    player_.jumped_ = true;
}

inline void PhysicsComponent::moveLeft(float& horizontalAcceleration)
{
    horizontalAcceleration = -20.0;
    if (!player_.jumped_ && player_.velocity.x > 0) player_.state = Player::State::Sliding;
}

inline void PhysicsComponent::moveRight(float& horizontalAcceleration)
{
    horizontalAcceleration = 20;
    if (!player_.jumped_ && player_.velocity.x < 0) player_.state = Player::State::Sliding;
}

inline float PhysicsComponent::getMaxHorizontalSpeed(bool running)
{
    return running ? horizontalMaxSpeedRun_ : horizontalMaxSpeedWalk_;
}

void PhysicsComponent::simulate(double dt)
{
    auto keys = Context::getKeyboardState();

    player_.velocity.x *=0.91;

    player_.velocity.y += (grav_ * dt);

    if (keys->up)
    {
        if (!player_.jumped_)
        {
            Context::getAudio()->playSample(core::AudioSample::PlayerJump);
            jump();
        }
        else
        {
            player_.velocity.y -= 255.0 * dt;
        } 
    }

    float horizontalAcceleration{};

    if (keys->left) moveLeft(horizontalAcceleration);
    if (keys->right) moveRight(horizontalAcceleration);

    if (abs(player_.velocity.x) >= getMaxHorizontalSpeed(keys->run)) 
    {
        horizontalAcceleration *= 0.5f;
    }

    player_.velocity.x += horizontalAcceleration;

    player_.setAnimationSpeed((horizontalMaxSpeedRun_ * 0.8 - abs(player_.velocity.x)) * 0.2 );


    player_.position += player_.velocity * dt;

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
            player_.position.y = object.position.y - player_.size.y + 1;
            player_.velocity.y = 0;
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
