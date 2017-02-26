#include "SmallBrick.hpp"

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"

namespace environment
{

SmallBrick::SmallBrick(math::Vector2f initialPosition, math::Vector2f velocity)
: Object(0),
    velocity_(velocity)
{
    bitmap_ = new AnimatedBitmap({
    BitmapType::SMALL_BRICK_1,
    BitmapType::SMALL_BRICK_2},
    20,
    *Context::getBitmapsContainer());


    size.y = Context::getBitmapsContainer()->get(BitmapType::SMALL_BRICK_1)->getHeight();
    size.x = Context::getBitmapsContainer()->get(BitmapType::SMALL_BRICK_1)->getWidth();
    position = initialPosition - size / 2.0f;

    collidable = false;
}

void SmallBrick::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
    bitmap_->nextFrame();
}

void SmallBrick::update(std::vector<Object*> gameObjects)
{
    (void) gameObjects;

    velocity_.y += 0.4f;

    position += velocity_;

    if ( position.y > 800)       // TODO: use real screen size for killing particles
    {
        dead = true;
    }
}

void SmallBrick::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
