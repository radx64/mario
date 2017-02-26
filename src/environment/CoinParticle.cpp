#include "CoinParticle.hpp"

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"

namespace environment
{

CoinParticle::CoinParticle(math::Vector2f initialPosition)
: Object(0)
{
    bitmap_ = new AnimatedBitmap({
    BitmapType::COIN_PARTICLE_0,
    BitmapType::COIN_PARTICLE_1,
    BitmapType::COIN_PARTICLE_2,
    BitmapType::COIN_PARTICLE_3},
    2,
    *Context::getBitmapsContainer());

    size.y = Context::getBitmapsContainer()->get(BitmapType::COIN_PARTICLE_0)->getHeight();
    size.x = Context::getBitmapsContainer()->get(BitmapType::COIN_PARTICLE_0)->getWidth();
    position = initialPosition_ = initialPosition - size / 2.0f;
    position.y -= size.y;

    collidable = false;
}

void CoinParticle::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
    bitmap_->nextFrame();
}

void CoinParticle::onUpdate(std::vector<Object*> gameObjects)
{
    (void) gameObjects;
    lifetime_++;

    position.y = initialPosition_.y - sin(lifetime_/10.0)*64.0f;

    if ( lifetime_ > 30)
    {
        dead = true;
    }
}

void CoinParticle::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
