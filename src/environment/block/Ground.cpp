#include "environment/block/Ground.hpp"

#include <SDL2/SDL.h>

#include "SpritesContainer.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"
#include "Sprite.hpp"


namespace environment
{
namespace block
{

Ground::Ground() : Object(ObjectType::Environment)
{
    sprite_ = Context::getSprites()->get(SpriteType::GROUND_RED);
    size.y = sprite_->getHeight();
    size.x = sprite_->getWidth();

    collidable = true;
}

void Ground::draw(double delta_time)
{
    (void) delta_time;
    sprite_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Ground::onUpdate(std::vector<Object*> gameObjects, double timeStep)
{
    (void) gameObjects;
    (void) timeStep;
}

void Ground::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace block
}  // namespace environment
