#include "character/player/PhysicsComponent.hpp"

#include <algorithm>
#include <cmath>

#include "Camera.hpp"
#include "Constants.hpp"
#include "Context.hpp"
#include "core/Audio.hpp"
#include "environment/Fireball.hpp"
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

void PhysicsComponent::input()
{
    auto keys = Context::getKeyboardState();

    if (keys->up)
    {
        if (player_.on_ground_)
        {
            Context::getAudio()->playSample(core::AudioSample::PlayerJump);
            jump();
        }
        else
        {
            if(player_.velocity.y > 0)  /* falling down */
            {
                verticalAcceleration = std::min(300.0, verticalAcceleration);   /* slowing fall down */
            }
            else    /* raising up */
            {
                verticalAcceleration = std::min(300.0, verticalAcceleration);
            }
        }
    }

    if (keys->fire && fireCooldown <= 0)
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
        fireCooldown = 1;
    }

    move_sideways(keys);
    if (keys->down) player_.crouched_ = true; else player_.crouched_ = false;

    if (abs(player_.velocity.x) >= get_max_running_speed(keys->run))
    {
        horizontalAcceleration *= 0.1f;
    }
}

inline void PhysicsComponent::bounce_of_ceiling()
{
    if (player_.velocity.y < 0.0) player_.velocity.y *= -1.0;
}

inline void PhysicsComponent::jump()
{
    player_.velocity.y = -200.0; /* need instatant jump velociy */
    verticalAcceleration = 130.0;
    player_.on_ground_ = false;
}

inline void PhysicsComponent::move_sideways(KeyboardState* keys)
{
    if (player_.crouched_)
    {
        horizontalAcceleration = 0.0;
    }
    else
    {
        if (keys->left) horizontalAcceleration = -800.0;
        if (keys->right) horizontalAcceleration = 800.0;

        if (!keys->left && !keys->right) horizontalAcceleration = 0.0;

    }
}

inline double PhysicsComponent::get_max_running_speed(bool running)
{
    return running ? max_run_speed_ : max_walk_speed_;
}

void PhysicsComponent::simulate(double dt)
{
    if (fireCooldown >= 0) fireCooldown-=dt;

    if (std::fabs(player_.velocity.x) > 5.0)
    {
        if (horizontalAcceleration!= 0 &&
            std::signbit(player_.velocity.x) != std::signbit(horizontalAcceleration))
        {
            player_.state = Player::State::Sliding;
        }
        else
        {
            player_.state = Player::State::Running;
        }
    }
    else
        player_.state = Player::State::Standing;

    if (!player_.on_ground_) player_.state = Player::State::Jumping;
    if (player_.crouched_ ) player_.state = Player::State::Crouching;


    verticalAcceleration += (constant::GRAVITY) * dt;

    player_.velocity.x += horizontalAcceleration * dt;
    player_.velocity.y += verticalAcceleration * dt;

    player_.velocity.x *= 0.95;
    player_.position += player_.velocity * dt;

    auto running_animation_delay = (1.0 - (abs(player_.velocity.x) / (max_run_speed_ + 10.0))) * dt * 25.0;
    player_.setAnimationDelay(running_animation_delay);


    Context::getCamera()->setX(player_.position.x);
    Context::getCamera()->setY(player_.position.y);
}

void PhysicsComponent::on_collision(Collision collision, Object& object)
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
            if (player_.velocity.y > 0) player_.velocity.y = 0;
            player_.position.y = object.position.y - player_.size.y + 1;
            player_.on_ground_ = true;
            verticalAcceleration = 0.0;
        }
    }

    if (collision.get() == Collision::State::Top)
    {
        bounce_of_ceiling();
    }

    if (collision.get() == Collision::State::Left)
    {
        if (player_.velocity.x < 0) player_.velocity.x = 0;
        if (horizontalAcceleration < 0) horizontalAcceleration = 0;
        player_.position.x = object.position.x + object.size.x;
    }

    if (collision.get() == Collision::State::Right)
    {
        if (player_.velocity.x > 0) player_.velocity.x = 0;
        if (horizontalAcceleration > 0) horizontalAcceleration = 0;
        player_.position.x = object.position.x - player_.size.x;
        
    }
}

}  // namespace player
}  // namespace character
