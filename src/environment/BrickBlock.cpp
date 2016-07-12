#include "BrickBlock.hpp"

#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include <SDL2/SDL.h>

namespace environment
{

BrickBlock::BrickBlock(Context& context, int type) : Object(type), context_(context)
{
    bitmap_ = context_.getBitmapsContainer()->get(BitmapType::BRICK_RED);

    h = bitmap_->getHeight();
    w = bitmap_->getWidth();
}

void BrickBlock::draw()
{
    bitmap_->draw(x,y);
}

void BrickBlock::simulate(std::vector<Object*> gameObjects)
{
    Object::simulate(gameObjects);
}

void BrickBlock::onCollisionWith(Collision collision, Object& object)
{

    if (collision.get() == Collision::State::Bottom)
    {
        hitCount_++;
        if (hitCount_ % 2 == 0)
        {
            bitmap_ = context_.getBitmapsContainer()->get(BitmapType::BRICK_RED);
        }
        else
        {
            bitmap_ = context_.getBitmapsContainer()->get(BitmapType::GROUND_RED);
        }
    }
    (void) object;
}

}  // namespace environment
