#include "BrickBlock.hpp"

#include <SDL2/SDL.h>

#include "BitmapsContainer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"
#include "environment/SmallBrick.hpp"
#include "World.hpp"

#include <iostream>

namespace environment
{

BrickBlock::BrickBlock(int type) : Object(type)
{
    bitmap_ = Context::getBitmapsContainer()->get(BitmapType::BRICK_RED);

    h = bitmap_->getHeight();
    w = bitmap_->getWidth();
}

void BrickBlock::draw()
{
    bitmap_->draw(Context::getCameraRenderer(), x, y);
}

void BrickBlock::update(std::vector<Object*> gameObjects)
{
    Object::update(gameObjects);
    draw();
}

void BrickBlock::onCollisionWith(Collision collision, Object& object)
{
    (void) object;
    if (collision.get() == Collision::State::Bottom && !dead)
    {
        dead = true;
        double spawn_x = x + (w / 2.0);
        double spawn_y = y + (h / 2.0);
        Object* brick = new SmallBrick(spawn_x, spawn_y, 1.0, -7.0);
        Context::getWorld()->level.toSpawnObjects.push_back(brick);
        brick = new SmallBrick(spawn_x, spawn_y, 1.0, -5.0);
        Context::getWorld()->level.toSpawnObjects.push_back(brick);
        brick = new SmallBrick(spawn_x, spawn_y, -1.0, -7.0);
        Context::getWorld()->level.toSpawnObjects.push_back(brick);
        brick = new SmallBrick(spawn_x, spawn_y, -1.0, -5.0);
        Context::getWorld()->level.toSpawnObjects.push_back(brick);
    }
}

}  // namespace environment
