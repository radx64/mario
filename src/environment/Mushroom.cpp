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
    velocity.x = 0.8;
}

void Mushroom::draw()
{
    sprite_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Mushroom::onUpdate(std::vector<Object*> gameObjects)
{
    velocity.y += grav_;
    findCollisions(gameObjects);
    position += velocity;
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
