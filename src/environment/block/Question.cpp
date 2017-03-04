#include "environment/block/Question.hpp"

#include <cmath>

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include "environment/CoinParticle.hpp"
#include "graphics/CameraRenderer.hpp"
#include "World.hpp"

namespace environment
{
namespace block
{

Question::Question(math::Vector2f initialPosition) : Object(ObjectType::Environment)
{
    position = originalPosition = initialPosition;
    fullAnimation_ = new AnimatedBitmap({
        BitmapType::QUESTIONBLOCK_0,
        BitmapType::QUESTIONBLOCK_1,
        BitmapType::QUESTIONBLOCK_2,
        BitmapType::QUESTIONBLOCK_1},
        10,
        *Context::getBitmapsContainer()
    );

    depletedAnimation_ = new AnimatedBitmap({BitmapType::QUESTIONBLOCK_USED}, 1,
        *Context::getBitmapsContainer()
    );

    currentAnimation_= fullAnimation_;

    size.y = Context::getBitmapsContainer()->get(BitmapType::QUESTIONBLOCK_0)->getHeight();
    size.x = Context::getBitmapsContainer()->get(BitmapType::QUESTIONBLOCK_0)->getWidth();

    collidable = true;
}

void Question::draw()
{
    if (!depleted_)
    {
        currentAnimation_ = fullAnimation_;
    }
    else
    {
        currentAnimation_ = depletedAnimation_;
    }

    currentAnimation_->draw(Context::getCameraRenderer(), position.x, position.y);
    currentAnimation_->nextFrame();
}

void Question::onUpdate(std::vector<Object*> gameObjects)
{
    (void) gameObjects;
    if (bounce_)
    {
        bounceTick_++;
        position.y = originalPosition.y - sin(bounceTick_/3.0)*8.0f;

        if (bounceTick_ >= 10)
        {
            bounce_ = false;
            bounceTick_ = 0;
            position.y = originalPosition.y;
        }
    }

}

}  // namespace block
}  // namespace environment
