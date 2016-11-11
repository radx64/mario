#include "GroundBlock.hpp"

#include <SDL2/SDL.h>

#include "BitmapsContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"


namespace environment
{

GroundBlock::GroundBlock(int type) : Object(type)
{
    bitmap_ = Context::getBitmapsContainer()->get(BitmapType::GROUND_RED);

    size.y = bitmap_->getHeight();
    size.x = bitmap_->getWidth();
}

void GroundBlock::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
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
