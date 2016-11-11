#include "Background.hpp"

#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"

namespace environment
{

Background::Background(BitmapType bitmap) : Object(0)
{
    bitmap_ = Context::getBitmapsContainer()->get(bitmap);
    size.y = bitmap_->getHeight();
    size.x = bitmap_->getWidth();
}

void Background::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Background::update(std::vector<Object*> gameObjects)
{
    (void) gameObjects;
    draw();
}

void Background::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
