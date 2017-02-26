#include "GroundBlock.hpp"

#include <SDL2/SDL.h>

#include "BitmapsContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"


namespace environment
{

GroundBlock::GroundBlock() : Object(ObjectType::Environment)
{
    bitmap_ = Context::getBitmapsContainer()->get(BitmapType::GROUND_RED);
    size.y = bitmap_->getHeight();
    size.x = bitmap_->getWidth();

    collidable = true;
}

void GroundBlock::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void GroundBlock::onUpdate(std::vector<Object*> gameObjects)
{
    (void) gameObjects;
}

void GroundBlock::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
