#include "Fireball.hpp"

#include <SDL2/SDL.h>

#include "AnimatedSprite.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"
#include "Sprite.hpp"
#include "SpritesContainer.hpp"

namespace environment
{

Fireball::Fireball(math::Vector2f initialPosition, math::Vector2f velocity)
: Object(ObjectType::Particle)
{
    this->velocity = velocity;
    bitmap_ = new AnimatedSprite({
    SpriteType::FIREBALL_1,
    SpriteType::FIREBALL_2,
    SpriteType::FIREBALL_3,
    SpriteType::FIREBALL_4},
    5,
    *Context::getSpritesContainer());

    size.x = Context::getSpritesContainer()->get(SpriteType::FIREBALL_1)->getWidth();
    size.y = Context::getSpritesContainer()->get(SpriteType::FIREBALL_1)->getHeight();
    position = initialPosition - size / 2.0f;

    collidable = true;
    moving = true;
}

void Fireball::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
    bitmap_->nextFrame();
}

void Fireball::onUpdate(std::vector<Object*> gameObjects, double timeStep)
{
    findCollisions(gameObjects);
    (void) gameObjects;
    (void) timeStep;

    //velocity.y += .5f;

    position += velocity * timeStep;

    if (lifetime_ > 300)
    {
        dead = true;
    }

}

void Fireball::onCollisionWith(Collision collision, Object& object)
{
    if(object.type_ == ObjectType::Player) return;
    if(object.type_ == ObjectType::Particle) return;

    auto collisionSide = collision.get();

    if ((collisionSide == Collision::State::Top) && (velocity.y < 0)) velocity.y = -velocity.y;
    if ((collisionSide == Collision::State::Bottom) && (velocity.y > 0)) velocity.y = -velocity.y;
    if ((collisionSide == Collision::State::Left) && (velocity.x < 0)) velocity.x = -velocity.x;
    if ((collisionSide == Collision::State::Right) && (velocity.x > 0)) velocity.x = -velocity.x;


}

}  // namespace environment
