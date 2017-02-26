#include "Goomba.hpp"

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"
#include "World.hpp"
#include "math/Vector2.hpp"

namespace character
{
namespace goomba
{

Goomba::Goomba() : Object(ObjectType::Enemy)
{
    walking_ = new AnimatedBitmap({
        BitmapType::GOOMBA_WALK_0,
        BitmapType::GOOMBA_WALK_1},
        10,
        *Context::getBitmapsContainer()
    );

    squashed_ = new AnimatedBitmap({
        BitmapType::GOOMBA_SQUASHED},
        1,
        *Context::getBitmapsContainer()
    );

    currentAnimation_ = walking_;

    size.x = Context::getBitmapsContainer()->get(BitmapType::GOOMBA_WALK_0)->getHeight();
    size.y = Context::getBitmapsContainer()->get(BitmapType::GOOMBA_WALK_0)->getHeight();
    collidable = true;
    moving = true;
    velocity.x = -0.5;
}

void Goomba::draw()
{
    currentAnimation_->nextFrame();
    currentAnimation_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Goomba::onUpdate(std::vector<Object*> gameObjects)
{
    if(state_ == State::Walking)
    {
        velocity.y += grav_;
        findCollisions(gameObjects);
        position += velocity;
    }
    else if (state_ == State::Dying)
    {
        dyingCounter_ += 1;
        if(dyingCounter_ > 15)
        {
            dead = true;
        }
    }
}

void Goomba::onCollisionWith(Collision collision, Object& object)
{
    if (collision.get() == Collision::State::Top && state_ != State::Dying)
    {
        state_ = State::Dying;
        collidable = false;
        currentAnimation_ = squashed_;
        position.y += Context::getBitmapsContainer()->get(BitmapType::GOOMBA_SQUASHED)->getHeight();
        return;
    }

    if(collision.get() == Collision::State::Bottom)
    {
        velocity.y = 0;
        position.y = object.position.y - size.y + 1;
    }

    if (collision.get() == Collision::State::Left)
    {
        velocity.x = -velocity.x;
        position.x = object.position.x + size.x;
    }

    if (collision.get()== Collision::State::Right)
    {
         velocity.x = -velocity.x;
         position.x = object.position.x - size.x;
    }

}

}  // namespace goomba
}  // namespace character
