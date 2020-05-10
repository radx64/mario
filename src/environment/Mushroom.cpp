#include "environment/Mushroom.hpp"

#include "Camera.hpp"
#include "Context.hpp"
#include "Constants.hpp"
#include "graphics/CameraRenderer.hpp"
#include "math/Vector2.hpp"
#include "Sprite.hpp"
#include "SpritesContainer.hpp"

#include <iostream>

namespace environment
{

Mushroom::Mushroom() : Object(ObjectType::PowerUp)
{
    sprite_ = Context::getSprites()->get(SpriteType::MUSHROOM);

    size.x = sprite_->getHeight();
    size.y = sprite_->getHeight();
    collidable_ = true;
    moving_ = true;
    velocity.x = 32.0;
    velocity.y -= 5.0;
    state_ = State::Spawning;
}

void Mushroom::draw(double delta_time)
{
    (void) delta_time;
    sprite_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Mushroom::on_simulate(double delta_time)
{
    if (lifetime_ > 0.3)
    {
        state_ = State::Spawned;
    }

    if (state_ == State::Spawning)
    {
        position.y += velocity.y * delta_time;
        return;
    }

    velocity.y += constant::GRAVITY * delta_time;
    position += velocity * delta_time;
}

void Mushroom::on_collision(Collision collision, Object& object)
{
    if (object.type_ == ObjectType::Player)
    {
        dead_ = true;
    }

    if(collision.get() == Collision::State::Bottom)
    {
        velocity.y = 0;
        position.y = object.position.y - size.y + 1;
    }

    if (collision.get() == Collision::State::Left)
    {
        if(velocity.x < 0) velocity.x *= -1.0;
    }

    if (collision.get()== Collision::State::Right)
    {
        if(velocity.x > 0) velocity.x *= -1.0;
    }
}

}  // namespace environment
