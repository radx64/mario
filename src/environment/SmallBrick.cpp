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
    *Context::getSprites());


    size.y = Context::getSprites()->get(SpriteType::SMALL_BRICK_1)->getHeight();
    size.x = Context::getSprites()->get(SpriteType::SMALL_BRICK_1)->getWidth();
    position = initialPosition - size / 2.0f;

    collidable = false;
}

void SmallBrick::draw(double delta_time)
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
    bitmap_->nextFrame(delta_time);
}

void SmallBrick::on_simulate(double delta_time)
{
    velocity_.y += 600.0f * delta_time;
    position += velocity_ * delta_time;

    if ( position.y > 800)       // TODO: use real screen size for killing particles
    {
        dead = true;
    }
}

void SmallBrick::on_collision(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
