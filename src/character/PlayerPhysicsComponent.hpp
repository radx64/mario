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
    void bouceOfCeiling(Object* ceilingBlock);

    Player& player_;

    const float grav_ {0.28};
    const float horizontalMaxSpeed_ {7.0};
};


}  // namespace character

#endif  // CHARACTER_PLAYERGRAPHICSCOMPONENT_HPP_
