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

    enum class State
    {
        Standing,
        Sliding,
        Running,
        Jumping
    };

    Player(int type);

    virtual void update(std::vector<Object*> gameObjects) override;
    virtual void draw() override;
    void onCollisionWith(Collision collision, Object& object);

    bool jumped_{false};
    State state{State::Standing};

protected:
    PlayerGraphicsComponent graphics_;
    PlayerPhysicsComponent physics_;
};

}  // namespace character

#endif  // CHARACTER_PLAYER_HPP_
