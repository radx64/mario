#ifndef CHARACTER_PLAYER_PLAYER_HPP_
#define CHARACTER_PLAYER_PLAYER_HPP_

#include <vector>
#include <utility>

#include "character/player/GraphicsComponent.hpp"
#include "character/player/PhysicsComponent.hpp"
#include "Object.hpp"

class Context;

namespace character
{
namespace player
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

    Player();

    virtual void onUpdate(std::vector<Object*> gameObjects, double timeStep) override;
    virtual void draw() override;
    void onCollisionWith(Collision collision, Object& object);
    void setAnimationSpeed(short speed);

    bool jumped_{false};
    State state{State::Standing};

protected:
    GraphicsComponent graphics_;
    PhysicsComponent physics_;
};

}  // namespace player
}  // namespace character

#endif  // CHARACTER_PLAYER_PLAYER_HPP_
