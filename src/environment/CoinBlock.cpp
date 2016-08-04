#include "CoinBlock.hpp"

#include <iostream>

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"

namespace environment
{

CoinBlock::CoinBlock(Context& context, int type) : Object(type), context_(context)
{
    fullAnimation_ = new AnimatedBitmap({
        BitmapType::QUESTIONBLOCK_0,
        BitmapType::QUESTIONBLOCK_1,
        BitmapType::QUESTIONBLOCK_2,
        BitmapType::QUESTIONBLOCK_1},
        10,
        *context_.getBitmapsContainer()
    );

    depletedAnimation_ = new AnimatedBitmap({BitmapType::QUESTIONBLOCK_1}, 1,
        *context_.getBitmapsContainer()
    );


    currentAnimation_= fullAnimation_;

    coins_ = 10;

    h = context_.getBitmapsContainer()->get(BitmapType::QUESTIONBLOCK_0)->getHeight();
    w = context_.getBitmapsContainer()->get(BitmapType::QUESTIONBLOCK_0)->getWidth();
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

    currentAnimation_->draw(x,y);
    currentAnimation_->nextFrame();
}

void CoinBlock::update(std::vector<Object*> gameObjects)
{
    Object::update(gameObjects);
    draw();
}

void CoinBlock::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;

    if (collision.get() == Collision::State::Bottom && coins_!=0)
    {
        --coins_;
        std::cout << "COIN! Left inside: "<< static_cast<uint16_t>(coins_) << std::endl;
    }

}

}  // namespace environment
