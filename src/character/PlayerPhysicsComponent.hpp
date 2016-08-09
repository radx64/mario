#ifndef CHARACTER_PLAYERPHYSICSSCOMPONENT_HPP_
#define CHARACTER_PLAYERPHYSICSSCOMPONENT_HPP_

#include <vector>

#include "Collision.hpp"

class AnimatedBitmap;
class Context;
class Object;

namespace character
{
class Player;

class PlayerPhysicsComponent
{
public:
    PlayerPhysicsComponent(Player& player, Context& context);
    ~PlayerPhysicsComponent();
    void simulate();
    void onCollisionWith(Collision collision, Object& object);

protected:
    bool isObjectAt(std::vector<Object*> gameObjects, float x, float y);
    void bouceOfCeiling(Object* ceilingBlock);

    Context& context_;
    Player& player_;

    const float grav_ {0.28};
    const float horizontalMaxSpeed_ {7.0};
};


}  // namespace character

#endif  // CHARACTER_PLAYERGRAPHICSCOMPONENT_HPP_
