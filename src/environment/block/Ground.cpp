#include "environment/block/Ground.hpp"

#include <SDL2/SDL.h>

#include "Bitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"


namespace environment
{
namespace block
{

Ground::Ground() : Object(ObjectType::Environment)
{
    bitmap_ = Context::getBitmapsContainer()->get(BitmapType::GROUND_RED).get();
    size.y = bitmap_->getHeight();
    size.x = bitmap_->getWidth();

    collidable = true;
}

void Ground::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Ground::onUpdate(std::vector<Object*> gameObjects)
{
    (void) gameObjects;
}

void Ground::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace block
}  // namespace environment
