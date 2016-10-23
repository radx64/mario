#include "CoinBlock.hpp"

#include <iostream>

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "Camera.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"
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

    coins_ = 50;

    h = Context::getBitmapsContainer()->get(BitmapType::QUESTIONBLOCK_0)->getHeight();
    w = Context::getBitmapsContainer()->get(BitmapType::QUESTIONBLOCK_0)->getWidth();
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

    auto camera = Context::getCamera();
    currentAnimation_->draw(x - camera->getX(),y - camera->getY());
    currentAnimation_->nextFrame();
}

void CoinBlock::update(std::vector<Object*> gameObjects)
{
    Object::update(gameObjects);
    double y_bak = y;
    if (bounce_)
    {
        bounceTick_++;
        y = y - sin(bounceTick_/5.0)*32;

        if (bounceTick_ >= 12)
        {
            bounce_ = false;
            bounceTick_ = 0;
        }
    }

    draw();
    y = y_bak;
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
            std::cout << "COIN! Left inside: "<< static_cast<uint16_t>(coins_) << std::endl;
        }
    }

}

}  // namespace environment
