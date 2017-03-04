#include "environment/block/Mushroom.hpp"

#include "Context.hpp"
#include "environment/Mushroom.hpp"
#include "World.hpp"

namespace environment
{
namespace block
{

Mushroom::Mushroom(math::Vector2f position) : Question(position)
{}

void Mushroom::onCollisionWith(Collision collision, Object& object)
{
    (void) object;

    if (collision.get() == Collision::State::Bottom && !depleted_)
    {
        if (!bounce_)
        {
            bounce_ = true;
            bounceTick_ = 0;
            depleted_ = true;
            math::Vector2f spawnPoint = position;
            spawnPoint.x += size.x / 2.0f;
            Object* mushroom = new environment::Mushroom();
            mushroom->position = spawnPoint;
            Context::getWorld()->level.toSpawnObjects.push_back(mushroom);
        }
    }

}

}  // namespace block
}  // namespace environment
