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

Goomba::Goomba(int type) : Object(type)
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
    moving = true;
    velocity.x = -0.5;
}

void Goomba::draw()
{
    currentAnimation_->draw(Context::getCameraRenderer(), position.x, position.y);
    currentAnimation_->nextFrame();
}

void Goomba::update(std::vector<Object*> gameObjects)
{
    if(state_ == State::Walking)
    {
        velocity.y += grav_;
        Object::update(gameObjects);
        position += velocity;
    }
    else if (state_ == State::Dying)
    {
        currentAnimation_ = squashed_;
        velocity = {0.0f, 0.0f};
        dyingCounter_ += 1;

        if(dyingCounter_ > 10)
        {
            dead = true;
        }
    }
}

void Goomba::onCollisionWith(Collision collision, Object& object)
{
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

    if (collision.get() == Collision::State::Top && state_ != State::Dying)
    {
        state_ = State::Dying;
        //todo: need to do something with dynamicaly changing size while animation frames have different dimensions
        position.y += Context::getBitmapsContainer()->get(BitmapType::GOOMBA_SQUASHED)->getHeight();
        //dead = true;
    }

}

}  // namespace goomba
}  // namespace character
