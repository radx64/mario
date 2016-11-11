#include "CoinBlock.hpp"

#include <iostream>

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"
#include "World.hpp"

namespace environment
{

CoinBlock::CoinBlock(int type) : Object(type)
{
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
    double y_bak = position.y;
    if (bounce_)
    {
        bounceTick_++;
        position.y -= sin(bounceTick_/8.5)*32;

        if (bounceTick_ >= 30)
        {
            bounce_ = false;
            bounceTick_ = 0;
        }
    }

    draw();
    position.y = y_bak;
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
            --coins_;
            Context::getWorld()->coins_++;
        }
    }

}

}  // namespace environment
