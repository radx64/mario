#include "CoinBlock.hpp"

#include <iostream>

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "environment/CoinParticle.hpp"
#include "graphics/CameraRenderer.hpp"
#include "World.hpp"

namespace environment
{

CoinBlock::CoinBlock(int type, math::Vector2f initialPosition) : Object(type)
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

    depletedAnimation_ = new AnimatedBitmap({BitmapType::QUESTIONBLOCK_1}, 1,
        *Context::getBitmapsContainer()
    );

    currentAnimation_= fullAnimation_;

    coins_ = 10;

    size.y = Context::getBitmapsContainer()->get(BitmapType::QUESTIONBLOCK_0)->getHeight();
    size.x = Context::getBitmapsContainer()->get(BitmapType::QUESTIONBLOCK_0)->getWidth();
}

void CoinBlock::draw()
{
    if (coins_ != 0)
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

void CoinBlock::update(std::vector<Object*> gameObjects)
{
    Object::update(gameObjects);
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

void CoinBlock::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;

    if (collision.get() == Collision::State::Bottom && coins_!=0)
    {
        if (!bounce_)
        {
            bounce_ = true;
            bounceTick_ = 0;
            --coins_;
            Context::getWorld()->coins_++;
            math::Vector2f spawnPoint = position;
            spawnPoint.x += size.x / 2.0f;
            //spawnPoint.y -= size.y / 2.0f;
            Object* coin = new CoinParticle(spawnPoint);
            Context::getWorld()->level.toSpawnObjects.push_back(coin);
        }
    }

}

}  // namespace environment
