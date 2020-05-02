#include "character/player/PhysicsComponent.hpp"

#include <algorithm>
#include <cmath>

#include "Camera.hpp"
#include "Context.hpp"
#include "core/Audio.hpp"
#include "environment/Fireball.hpp"
#include "Player.hpp"
#include "KeyboardState.hpp"
#include "World.hpp"

#include <iostream>

namespace character
{
namespace player
{

PhysicsComponent::PhysicsComponent(Player& player)
: player_(player)
{}

inline void PhysicsComponent::bounce_of_ceiling()
{
    if (player_.velocity.y < 0.0) player_.velocity.y *= -1.0;
}

inline void PhysicsComponent::jump()
{
    player_.velocity.y = -210.0;
    player_.jumped_ = true;
}

inline void PhysicsComponent::moveLeft(float& horizontalAcceleration)
{
    if (player_.crouched_) return;
    horizontalAcceleration = -10.0;
    if (!player_.jumped_ && player_.velocity.x > 0) player_.state = Player::State::Sliding;
}

inline void PhysicsComponent::moveRight(float& horizontalAcceleration)
{
    if (player_.crouched_) return;
    horizontalAcceleration = 10;
    if (!player_.jumped_ && player_.velocity.x < 0) player_.state = Player::State::Sliding;
}

inline float PhysicsComponent::getMaxHorizontalSpeed(bool running)
{
    return running ? max_run_speed_ : max_walk_speed_;
}

void PhysicsComponent::simulate(double dt)
{
    auto keys = Context::getKeyboardState();

    player_.velocity.x *= 0.95;

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
            player_.velocity.y -= 155.0 * dt;
        } 
    }

    float horizontalAcceleration{};

    if (fireCooldown > 0) fireCooldown--;

    if (std::fabs(player_.velocity.x) > 5.0 )
        player_.state = Player::State::Running;
    else
        player_.state = Player::State::Standing;

    if (player_.jumped_) player_.state = Player::State::Jumping;
    if (player_.crouched_ ) player_.state = Player::State::Crouching;

    if (keys->left) moveLeft(horizontalAcceleration);
    if (keys->right) moveRight(horizontalAcceleration);
    if (keys->down) player_.crouched_ = true; else player_.crouched_ = false;

    if (abs(player_.velocity.x) >= getMaxHorizontalSpeed(keys->run)) 
    {
        horizontalAcceleration *= 0.01f;
    }

    player_.velocity.x += horizontalAcceleration;


    auto running_animation_delay = (1.0 - (abs(player_.velocity.x) / max_run_speed_)) * dt * 15.0;
    player_.setAnimationDelay(running_animation_delay);

    player_.position += player_.velocity * dt;

    Context::getCamera()->setX(player_.position.x);
    Context::getCamera()->setY(player_.position.y);

    if (keys->fire && fireCooldown == 0)
    {
        math::Vector2f spawnPoint = player_.position;
        spawnPoint.x += player_.size.x / 2.0f;
        spawnPoint.y += player_.size.y / 2.0f;

        math::Vector2f spawnVelocity = player_.velocity;
        spawnVelocity.x *= 2.5f;
        spawnVelocity.y = 70.0f;

        Object* fireball = new environment::Fireball(spawnPoint, spawnVelocity);
        Context::getWorld()->level.toSpawnObjectsInFore.push_back(fireball);
        Context::getAudio()->playSample(core::AudioSample::Fireball);
        fireCooldown = 30;
    }
}

void PhysicsComponent::onCollisionWith(Collision collision, Object& object)
{

    if(object.type_ == ObjectType::Fireball) return;

    if (collision.get() == Collision::State::Bottom)
    {
        if (object.type_ == ObjectType::Enemy)
        {
            jump();
        }
        else
        {
            player_.position.y = object.position.y - player_.size.y + 1;
            if (player_.velocity.y > 0) player_.velocity.y = 0;
            player_.jumped_ = false;
        }
    }

    if (collision.get() == Collision::State::Top)
    {
        bounce_of_ceiling();
    }

    if (collision.get() == Collision::State::Left)
    {
        player_.position.x = object.position.x + object.size.x;
        player_.velocity.x = 0;
    }

    if (collision.get() == Collision::State::Right)
    {
        player_.position.x = object.position.x - player_.size.x ;
        player_.velocity.x = 0;
    }
}

}  // namespace player
}  // namespace character
