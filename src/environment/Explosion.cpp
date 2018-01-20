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
    5,
    *Context::getSpritesContainer());


    size.y = Context::getSpritesContainer()->get(SpriteType::SMALL_BRICK_1)->getHeight();
    size.x = Context::getSpritesContainer()->get(SpriteType::SMALL_BRICK_1)->getWidth();
    position = initialPosition - size / 2.0f;

    collidable = false;
}

void Explosion::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
    bitmap_->nextFrame();
}

void Explosion::onUpdate(std::vector<Object*> gameObjects, double timeStep)
{
    (void) gameObjects;
    (void) timeStep;

    if (lifetime_ > 15)
    {
        dead = true;
    }

}

void Explosion::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
