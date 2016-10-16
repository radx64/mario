#ifndef CHARACTER_PLAYER_HPP_
#define CHARACTER_PLAYER_HPP_

#include <vector>
#include <utility>

#include "AnimatedBitmap.hpp"
#include "Object.hpp"
#include "PlayerGraphicsComponent.hpp"
#include "PlayerPhysicsComponent.hpp"

class Context;

namespace character
{

class Player : public Object
{
public:
    Player(int type);
    virtual void update(std::vector<Object*> gameObjects) override;
    void onCollisionWith(Collision collision, Object& object);
    bool jumped_{false};

protected:
    virtual void draw();
    virtual void simulate();

    PlayerGraphicsComponent graphics_;
    PlayerPhysicsComponent physics_;
};

}  // namespace character

#endif  // CHARACTER_PLAYER_HPP_
