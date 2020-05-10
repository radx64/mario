#include "environment/block/Bricks.hpp"

#include <cmath>
#include <SDL2/SDL.h>

#include "SpritesContainer.hpp"
#include "Context.hpp"
#include "core/Audio.hpp"
#include "environment/SmallBrick.hpp"
#include "graphics/CameraRenderer.hpp"
#include "math/Vector2.hpp"
#include "Sprite.hpp"
#include "World.hpp"

#include "character/player/Player.hpp"

namespace environment
{
namespace block
{

Bricks::Bricks(math::Vector2f initialPosition)  : Object(ObjectType::Environment)
{
    bitmap_ = Context::getSprites()->get(SpriteType::BRICK_RED);
    size.x = bitmap_->getWidth();
    size.y = bitmap_->getHeight();
    collidable_ = true;
    originalPosition = position = initialPosition;
}

void Bricks::draw(double delta_time)
{
    (void) delta_time;
    bitmap_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Bricks::on_simulate(double timeStep)
{
    (void) timeStep;
    if (bounce_)
    {
        bounceTick_+=timeStep;
        position.y = originalPosition.y - sin(bounceTick_*12.0)*8.0f;

        if (position.y > originalPosition.y)
        {
            bounce_ = false;
            bounceTick_ = 0;
            position.y = originalPosition.y;
        }
    }
}

void Bricks::on_collision(Collision collision, Object& object)
{
    if (object.type_ == ObjectType::Player)
    {
        if (collision.get() != Collision::State::Bottom) return;

        auto player = dynamic_cast<character::player::Player&>(object);


        if (!dead_ && player.power_level != character::player::Player::PowerLevel::Small)
        {
            dead_ = true;
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
        else
        {
            bounce_ = true;
            Context::getAudio()->playSample(core::AudioSample::BlockHit);
        }
    }


}

}  // namespace block
}  // namespace environment
