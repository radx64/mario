#include "CoinParticle.hpp"

#include <SDL2/SDL.h>

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
    2,
    *Context::getSpritesContainer());

    size.y = Context::getSpritesContainer()->get(SpriteType::COIN_PARTICLE_0)->getHeight();
    size.x = Context::getSpritesContainer()->get(SpriteType::COIN_PARTICLE_0)->getWidth();
    position = initialPosition_ = initialPosition - size / 2.0f;
    position.y -= size.y;

    collidable = false;
}

void CoinParticle::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
    bitmap_->nextFrame();
}

void CoinParticle::onUpdate(std::vector<Object*> gameObjects, double timeStep)
{
    (void) gameObjects;
    (void) timeStep;
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
