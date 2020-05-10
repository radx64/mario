#include "Explosion.hpp"

#include <SDL2/SDL.h>

#include "AnimatedSprite.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"
#include "Sprite.hpp"
#include "SpritesContainer.hpp"

namespace environment
{

Explosion::Explosion(math::Vector2f initialPosition)
: Object(ObjectType::Particle)
{
    bitmap_ = new AnimatedSprite({
    SpriteType::EXPLOSION_1,
    SpriteType::EXPLOSION_2,
    SpriteType::EXPLOSION_3},
    0.1,
    *Context::getSprites());

    size.y = Context::getSprites()->get(SpriteType::SMALL_BRICK_1)->getHeight();
    size.x = Context::getSprites()->get(SpriteType::SMALL_BRICK_1)->getWidth();
    position = initialPosition - size / 2.0f;

    collidable_ = false;
}

void Explosion::draw(double delta_time)
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
    bitmap_->nextFrame(delta_time);
}

void Explosion::on_simulate(double timeStep)
{
    (void) timeStep;

    if (lifetime_ > 1)
    {
        dead_ = true;
    }

}

void Explosion::on_collision(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
