#ifndef CHARACTER_PLAYER_PHYSICSSCOMPONENT_HPP_
#define CHARACTER_PLAYER_PHYSICSSCOMPONENT_HPP_

#include <vector>

#include "Collision.hpp"

class AnimatedBitmap;
class Object;

namespace character
{
namespace player
{
class Player;

class PhysicsComponent
{
public:
    PhysicsComponent(Player& player);
    void simulate(double dt);
    void onCollisionWith(Collision collision, Object& object);

protected:
    inline void bouceOfCeiling();
    inline void jump();
    inline void fall();
    inline void moveLeft(float& horizontalAcceleration);
    inline void moveRight(float& horizontalAcceleration);
    inline float getMaxHorizontalSpeed(bool running);

    Player& player_;

    const float grav_ {5.0};
    const float horizontalMaxSpeedWalk_ {40.0};
    const float horizontalMaxSpeedRun_ {200.0};
};

}  // namespace player
}  // namespace character

#endif  // CHARACTER_PLAYER_PHYSICSSCOMPONENT_HPP_
