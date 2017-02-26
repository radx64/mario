#include "BrickBlock.hpp"

#include <SDL2/SDL.h>

#include "BitmapsContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"
#include "environment/SmallBrick.hpp"
#include "World.hpp"
#include "math/Vector2.hpp"

#include <iostream>

namespace environment
{

BrickBlock::BrickBlock(int type) : Object(type)
{
    bitmap_ = Context::getBitmapsContainer()->get(BitmapType::BRICK_RED);
    size.x = bitmap_->getWidth();
    size.y = bitmap_->getHeight();
    collidable = true;
}

void BrickBlock::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void BrickBlock::onUpdate(std::vector<Object*> gameObjects)
{
    (void) gameObjects;
}

void BrickBlock::onCollisionWith(Collision collision, Object& object)
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

}  // namespace environment
