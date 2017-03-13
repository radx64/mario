#include "environment/Mushroom.hpp"

#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"
#include "math/Vector2.hpp"
#include "Sprite.hpp"
#include "SpritesContainer.hpp"

namespace environment
{

Mushroom::Mushroom() : Object(ObjectType::PowerUp)
{
    sprite_ = Context::getSpritesContainer()->get(SpriteType::MUSHROOM);

    size.x = sprite_->getHeight();
    size.y = sprite_->getHeight();
    collidable = true;
    moving = true;
    velocity.x = 32.0;
    state_ = State::Spawning;
}

void Mushroom::draw()
{
    sprite_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Mushroom::onUpdate(std::vector<Object*> gameObjects, double timeStep)
{

    if (lifetime_ > 50) state_ = State::Spawned;

    if (state_ == State::Spawning)
    {
        position.y -= 20.0 * timeStep;
        return;
    }

    velocity.y += grav_ * timeStep;
    findCollisions(gameObjects);
    position += velocity * timeStep;
}

void Mushroom::onCollisionWith(Collision collision, Object& object)
{
    if(collision.get() == Collision::State::Bottom)
    {
        velocity.y = 0;
        position.y = object.position.y - size.y + 1;
    }

    if (collision.get() == Collision::State::Left)
    {
        velocity.x = -velocity.x;
        position.x = object.position.x + size.x + 1;
    }

    if (collision.get()== Collision::State::Right)
    {
         velocity.x = -velocity.x;
         position.x = object.position.x - size.x - 1;
    }
}

}  // namespace environment
