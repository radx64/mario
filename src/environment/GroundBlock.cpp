#include "GroundBlock.hpp"

#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include <SDL2/SDL.h>

namespace environment
{

GroundBlock::GroundBlock(int type) : Object(type)
{
    bitmap_ = Context::getBitmapsContainer()->get(BitmapType::GROUND_RED);

    h = bitmap_->getHeight();
    w = bitmap_->getWidth();
}

void GroundBlock::draw()
{
    bitmap_->draw(x,y);
}

void GroundBlock::update(std::vector<Object*> gameObjects)
{
    Object::update(gameObjects);
    draw();
}

void GroundBlock::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
