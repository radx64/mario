#include "environment/block/Coins.hpp"

#include "Context.hpp"
#include "environment/CoinParticle.hpp"
#include "World.hpp"

namespace environment
{
namespace block
{

Coins::Coins(math::Vector2f position, uint8_t coins) 
: Question(position), coins_(coins)
{}

void Coins::onCollisionWith(Collision collision, Object& object)
{
    (void) object;

    if (collision.get() == Collision::State::Bottom && !depleted_)
    {
        if (!bounce_)
        {
            bounce_ = true;
            bounceTick_ = 0;
            --coins_;
            depleted_ = coins_ == 0;
            Context::getWorld()->coins_++;
            math::Vector2f spawnPoint = position;
            spawnPoint.x += size.x / 2.0f;
            Object* coin = new CoinParticle(spawnPoint);
            Context::getWorld()->level.toSpawnObjects.push_back(coin);
        }
    }

}

}  // namespace block
}  // namespace environment
