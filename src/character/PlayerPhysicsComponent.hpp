#ifndef CHARACTER_PLAYERPHYSICSSCOMPONENT_HPP_
#define CHARACTER_PLAYERPHYSICSSCOMPONENT_HPP_

#include <vector>

#include "Collision.hpp"

class AnimatedBitmap;
class Object;

namespace character
{
class Player;

class PlayerPhysicsComponent
{
public:
    PlayerPhysicsComponent(Player& player);
    ~PlayerPhysicsComponent();
    void simulate();
    void onCollisionWith(Collision collision, Object& object);

protected:
    void bouceOfCeiling();

    Player& player_;

    const float grav_ {0.20};
    const float horizontalMaxSpeedWalk_ {1.0};
    const float horizontalMaxSpeedRun_ {3.0};
};


}  // namespace character

#endif  // CHARACTER_PLAYERGRAPHICSCOMPONENT_HPP_
