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
        Jumping,
        Crouching
    };

    Player();

    virtual void on_simulate(double delta_time) override;
    virtual void draw(double delta_time) override;
    void on_input();
    void on_collision(Collision collision, Object& object);
    void setAnimationDelay(double delay);

    bool on_ground_{false};
    bool crouched_{false};
    State state{State::Standing};
    State previousState{State::Standing};

protected:
    GraphicsComponent graphics_;
    PhysicsComponent physics_;
};

}  // namespace player
}  // namespace character

#endif  // CHARACTER_PLAYER_PLAYER_HPP_
