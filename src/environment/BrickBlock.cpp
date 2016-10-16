#include "BrickBlock.hpp"

#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include <SDL2/SDL.h>

namespace environment
{

BrickBlock::BrickBlock(int type) : Object(type)
{
    bitmap_ = Context::getBitmapsContainer()->get(BitmapType::BRICK_RED);

    h = bitmap_->getHeight();
    w = bitmap_->getWidth();
}

void BrickBlock::draw()
{
    bitmap_->draw(x,y);
}

void BrickBlock::update(std::vector<Object*> gameObjects)
{
    Object::update(gameObjects);
    draw();
}

void BrickBlock::onCollisionWith(Collision collision, Object& object)
{

    if (collision.get() == Collision::State::Bottom)
    {
        hitCount_++;
        if (hitCount_ % 2 == 0)
        {
            bitmap_ = Context::getBitmapsContainer()->get(BitmapType::BRICK_RED);
        }
        else
        {
            bitmap_ = Context::getBitmapsContainer()->get(BitmapType::GROUND_RED);
        }
    }
    (void) object;
}

}  // namespace environment
