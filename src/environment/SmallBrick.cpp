#include "SmallBrick.hpp"

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"

namespace environment
{

SmallBrick::SmallBrick(double ix, double iy, double x_velocity, double y_velocity) 
: Object(0),
    x_velocity_(x_velocity),
    y_velocity_(y_velocity)
{
    bitmap_ = new AnimatedBitmap({
    BitmapType::SMALL_BRICK_1,
    BitmapType::SMALL_BRICK_2},
    20,
    *Context::getBitmapsContainer());


    h = Context::getBitmapsContainer()->get(BitmapType::SMALL_BRICK_1)->getHeight();
    w = Context::getBitmapsContainer()->get(BitmapType::SMALL_BRICK_1)->getWidth();
    x = ix - w / 2.0;
    y = iy - h / 2.0;
}

void SmallBrick::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), x, y);
    bitmap_->nextFrame();
}

void SmallBrick::update(std::vector<Object*> gameObjects)
{
    (void) gameObjects;

    y_velocity_ += 0.4;
    
    x += x_velocity_;
    y += y_velocity_;
    draw();

    if ( y > 800)       // TODO: use real screen size for killing this particle
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
