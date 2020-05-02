#include "character/goomba/Goomba.hpp"

#include "AnimatedSprite.hpp"
#include "SpritesContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "core/Audio.hpp"
#include "graphics/CameraRenderer.hpp"
#include "math/Vector2.hpp"
#include "Sprite.hpp"

namespace character
{
namespace goomba
{

Goomba::Goomba() : Object(ObjectType::Enemy)
{
    walking_ = new AnimatedSprite({
        SpriteType::GOOMBA_WALK_0,
        SpriteType::GOOMBA_WALK_1},
        0.3,
        *Context::getSprites()
    );

    squashed_ = new AnimatedSprite({
        SpriteType::GOOMBA_SQUASHED},
        1,
        *Context::getSprites()
    );

    currentAnimation_ = walking_;

    size.x = Context::getSprites()->get(SpriteType::GOOMBA_WALK_0)->getHeight();
    size.y = Context::getSprites()->get(SpriteType::GOOMBA_WALK_0)->getHeight();
    collidable = true;
    moving = true;
    velocity.x = -30.0;
}

void Goomba::draw(double delta_time)
{
    currentAnimation_->nextFrame(delta_time);
    currentAnimation_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Goomba::onUpdate(std::vector<Object*> gameObjects, double delta_time)
{
    if(state_ == State::Walking)
    {
        velocity.y += grav_ * delta_time;
        findCollisions(gameObjects);
        position += velocity * delta_time;
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

void Goomba::die()
{
    state_ = State::Dying;
    Context::getAudio()->playSample(core::AudioSample::Stomp);
    collidable = false;
    currentAnimation_ = squashed_;
    position.y += Context::getSprites()->get(SpriteType::GOOMBA_SQUASHED)->getHeight(); // TODO: remove this nasty hack
}

void Goomba::onCollisionWith(Collision collision, Object& object)
{
    if (object.type_ == ObjectType::Fireball)
    {
        die();
        return;
    }


    if (collision.get() == Collision::State::Top 
        && state_ != State::Dying 
        && object.type_ == ObjectType::Player)
    {
        die();
        return;
    }

    if(collision.get() == Collision::State::Bottom)
    {
        velocity.y = 0;
        position.y = object.position.y - size.y + 1;
    }

    if (collision.get() == Collision::State::Left)
    {
        if (velocity.x < 0.0) velocity.x = -velocity.x;
        position.x = object.position.x + size.x + 1;
    }

    if (collision.get()== Collision::State::Right)
    {
        if (velocity.x > 0.0) velocity.x = -velocity.x;
        position.x = object.position.x - size.x - 1;
    }

}

}  // namespace goomba
}  // namespace character
