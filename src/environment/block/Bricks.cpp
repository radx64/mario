#include "environment/block/Bricks.hpp"

#include <SDL2/SDL.h>

#include "SpritesContainer.hpp"
#include "Context.hpp"
#include "environment/SmallBrick.hpp"
#include "graphics/CameraRenderer.hpp"
#include "math/Vector2.hpp"
#include "Sprite.hpp"
#include "World.hpp"

namespace environment
{
namespace block
{

Bricks::Bricks() : Object(ObjectType::Environment)
{
    bitmap_ = Context::getSpritesContainer()->get(SpriteType::BRICK_RED);
    size.x = bitmap_->getWidth();
    size.y = bitmap_->getHeight();
    collidable = true;
}

void Bricks::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Bricks::onUpdate(std::vector<Object*> gameObjects)
{
    (void) gameObjects;
}

void Bricks::onCollisionWith(Collision collision, Object& object)
{
    (void) object;
    if (collision.get() == Collision::State::Bottom && !dead)
    {
        dead = true;
        math::Vector2f spawnPoint = position + size / 2.0f;

        Object* brick = new SmallBrick(spawnPoint, {0.8, -7.0});
        Context::getWorld()->level.toSpawnObjects.push_back(brick);
        brick = new SmallBrick(spawnPoint, {0.8, -5.0});
        Context::getWorld()->level.toSpawnObjects.push_back(brick);
        brick = new SmallBrick(spawnPoint, {-0.8, -7.0});
        Context::getWorld()->level.toSpawnObjects.push_back(brick);
        brick = new SmallBrick(spawnPoint, {-0.8, -5.0});
        Context::getWorld()->level.toSpawnObjects.push_back(brick);
    }
}

}  // namespace block
}  // namespace environment
