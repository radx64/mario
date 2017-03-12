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
        10,
        *Context::getSpritesContainer()
    );

    squashed_ = new AnimatedSprite({
        SpriteType::GOOMBA_SQUASHED},
        1,
        *Context::getSpritesContainer()
    );

    currentAnimation_ = walking_;

    size.x = Context::getSpritesContainer()->get(SpriteType::GOOMBA_WALK_0)->getHeight();
    size.y = Context::getSpritesContainer()->get(SpriteType::GOOMBA_WALK_0)->getHeight();
    collidable = true;
    moving = true;
    velocity.x = -50.0;
}

void Goomba::draw()
{
    currentAnimation_->nextFrame();
    currentAnimation_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Goomba::onUpdate(std::vector<Object*> gameObjects, double timeStep)
{
    (void) timeStep;
    if(state_ == State::Walking)
    {
        velocity.y += grav_;
        findCollisions(gameObjects);
        position += velocity * timeStep;
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
    if (collision.get() == Collision::State::Top 
        && state_ != State::Dying 
        && object.type_ == ObjectType::Player)
    {
        state_ = State::Dying;
        Context::getAudio()->playSample(core::AudioSample::Stomp);
        collidable = false;
        currentAnimation_ = squashed_;
        position.y += Context::getSpritesContainer()->get(SpriteType::GOOMBA_SQUASHED)->getHeight(); // TODO: remove this nasty hack
        return;
    }

    if(collision.get() == Collision::State::Bottom)
    {
        velocity.y = 0;
        position.y = object.position.y - size.y + 2;
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
