#include "CoinParticle.hpp"

#include <SDL2/SDL.h>
#include <cmath>

#include "AnimatedSprite.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"
#include "Sprite.hpp"
#include "SpritesContainer.hpp"

namespace environment
{

CoinParticle::CoinParticle(math::Vector2f initialPosition)
: Object(ObjectType::Particle)
{
    bitmap_ = new AnimatedSprite({
    SpriteType::COIN_PARTICLE_0,
    SpriteType::COIN_PARTICLE_1,
    SpriteType::COIN_PARTICLE_2,
    SpriteType::COIN_PARTICLE_3},
    0.1,
    *Context::getSprites());

    size.y = Context::getSprites()->get(SpriteType::COIN_PARTICLE_0)->getHeight();
    size.x = Context::getSprites()->get(SpriteType::COIN_PARTICLE_0)->getWidth();
    position = initialPosition_ = initialPosition - size / 2.0f;
    position.y -= size.y;

    collidable = false;
}

void CoinParticle::draw(double delta_time)
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
    bitmap_->nextFrame(delta_time);
}

void CoinParticle::on_simulate(double delta_time)
{
    lifetime_+=delta_time;

    position.y = (initialPosition_.y - sin(lifetime_*4.0)*64.0f) ;

    if (position.y > initialPosition_.y)
    {
        dead = true;
    }
}

void CoinParticle::on_collision(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
