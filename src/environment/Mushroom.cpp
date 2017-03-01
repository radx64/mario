#include "environment/Mushroom.hpp"

#include "AnimatedBitmap.hpp"
#include "Bitmap.hpp"
#include "BitmapsContainer.hpp"
#include "graphics/CameraRenderer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "math/Vector2.hpp"

namespace environment
{

Mushroom::Mushroom() : Object(ObjectType::PowerUp)
{
    bitmap_ = Context::getBitmapsContainer()->get(BitmapType::MUSHROOM);

    size.x = bitmap_->getHeight();
    size.y = bitmap_->getHeight();
    collidable = true;
    moving = true;
    velocity.x = 0.8;
}

void Mushroom::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
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
