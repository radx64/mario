#include "SmallBrick.hpp"

#include <SDL2/SDL.h>

#include "AnimatedSprite.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"
#include "Sprite.hpp"
#include "SpritesContainer.hpp"

namespace environment
{

SmallBrick::SmallBrick(math::Vector2f initialPosition, math::Vector2f velocity)
: Object(ObjectType::Particle),
    velocity_(velocity)
{
    bitmap_ = new AnimatedSprite({
    SpriteType::SMALL_BRICK_1,
    SpriteType::SMALL_BRICK_2},
    20,
    *Context::getSpritesContainer());


    size.y = Context::getSpritesContainer()->get(SpriteType::SMALL_BRICK_1)->getHeight();
    size.x = Context::getSpritesContainer()->get(SpriteType::SMALL_BRICK_1)->getWidth();
    position = initialPosition - size / 2.0f;

    collidable = false;
}

void SmallBrick::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
    bitmap_->nextFrame();
}

void SmallBrick::onUpdate(std::vector<Object*> gameObjects, double timeStep)
{
    (void) gameObjects;
    (void) timeStep;

    velocity_.y += 8.0f;

    position += velocity_ * timeStep;

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
