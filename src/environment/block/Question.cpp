#include "environment/block/Question.hpp"

#include <cmath>

#include "AnimatedSprite.hpp"
#include "SpritesContainer.hpp"
#include "Context.hpp"
#include "environment/CoinParticle.hpp"
#include "graphics/CameraRenderer.hpp"
#include "Sprite.hpp"
#include "World.hpp"

namespace environment
{
namespace block
{

Question::Question(math::Vector2f initialPosition) : Object(ObjectType::Environment)
{
    position = originalPosition = initialPosition;
    fullAnimation_ = new AnimatedSprite({
        SpriteType::QUESTIONBLOCK_0,
        SpriteType::QUESTIONBLOCK_1,
        SpriteType::QUESTIONBLOCK_2,
        SpriteType::QUESTIONBLOCK_1},
        0.5,
        *Context::getSprites()
    );

    depletedAnimation_ = new AnimatedSprite({SpriteType::QUESTIONBLOCK_USED}, 1,
        *Context::getSprites()
    );

    currentAnimation_= fullAnimation_;

    size.y = Context::getSprites()->get(SpriteType::QUESTIONBLOCK_0)->getHeight();
    size.x = Context::getSprites()->get(SpriteType::QUESTIONBLOCK_0)->getWidth();

    collidable = true;
}

void Question::draw(double delta_time)
{
    if (depleted_)
    {
        currentAnimation_ = depletedAnimation_;
    }
    else
    {
        currentAnimation_ = fullAnimation_;
    }

    currentAnimation_->draw(Context::getCameraRenderer(), position.x, position.y);
    currentAnimation_->nextFrame(delta_time);
}

void Question::onUpdate(std::vector<Object*> gameObjects, double timeStep)
{
    (void) gameObjects;
    (void) timeStep;
    if (bounce_)
    {
        bounceTick_+=timeStep;
        position.y = originalPosition.y - sin(bounceTick_*12.0)*8.0f;

        if (position.y > originalPosition.y)
        {
            bounce_ = false;
            bounceTick_ = 0;
            position.y = originalPosition.y;
        }
    }

}

}  // namespace block
}  // namespace environment
