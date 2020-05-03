#include "environment/block/Bricks.hpp"

#include <SDL2/SDL.h>

#include "SpritesContainer.hpp"
#include "Context.hpp"
#include "core/Audio.hpp"
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
    bitmap_ = Context::getSprites()->get(SpriteType::BRICK_RED);
    size.x = bitmap_->getWidth();
    size.y = bitmap_->getHeight();
    collidable = true;
}

void Bricks::draw(double delta_time)
{
    (void) delta_time;
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Bricks::on_simulate(double timeStep)
{
    (void) timeStep;
}

void Bricks::on_collision(Collision collision, Object& object)
{
    (void) object;
    if (collision.get() == Collision::State::Bottom && !dead)
    {
        dead = true;
        math::Vector2f spawnPoint = position + size / 2.0f;
        Context::getAudio()->playSample(core::AudioSample::BlockBreak);

        Object* brick = new SmallBrick(spawnPoint, {15.8, -200.0});
        Context::getWorld()->level.toSpawnObjectsInFore.push_back(brick);
        brick = new SmallBrick(spawnPoint, {15.8, -100.0});
        Context::getWorld()->level.toSpawnObjectsInFore.push_back(brick);
        brick = new SmallBrick(spawnPoint, {-15.8, -200.0});
        Context::getWorld()->level.toSpawnObjectsInFore.push_back(brick);
        brick = new SmallBrick(spawnPoint, {-15.8, -100.0});
        Context::getWorld()->level.toSpawnObjectsInFore.push_back(brick);
    }
}

}  // namespace block
}  // namespace environment
