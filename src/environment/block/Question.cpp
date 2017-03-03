#include "environment/block/Question.hpp"

#include <cmath>

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include "environment/CoinParticle.hpp"
#include "environment/Mushroom.hpp"
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

Coins::Coins(math::Vector2f position, uint8_t coins) 
: Question(position), coins_(coins)
{}

void Coins::onCollisionWith(Collision collision, Object& object)
{
    (void) object;

    if (collision.get() == Collision::State::Bottom && !depleted_)
    {
        if (!bounce_)
        {
            bounce_ = true;
            bounceTick_ = 0;
            --coins_;
            depleted_ = coins_ == 0;
            Context::getWorld()->coins_++;
            math::Vector2f spawnPoint = position;
            spawnPoint.x += size.x / 2.0f;
            Object* coin = new CoinParticle(spawnPoint);
            Context::getWorld()->level.toSpawnObjects.push_back(coin);
        }
    }

}


Mushroom::Mushroom(math::Vector2f position) : Question(position)
{}

void Mushroom::onCollisionWith(Collision collision, Object& object)
{
    (void) object;

    if (collision.get() == Collision::State::Bottom && !depleted_)
    {
        if (!bounce_)
        {
            bounce_ = true;
            bounceTick_ = 0;
            depleted_ = true;
            math::Vector2f spawnPoint = position;
            spawnPoint.x += size.x / 2.0f;
            Object* mushroom = new environment::Mushroom();
            mushroom->position = spawnPoint;
            Context::getWorld()->level.toSpawnObjects.push_back(mushroom);
        }
    }

}

}  // namespace block
}  // namespace environment
