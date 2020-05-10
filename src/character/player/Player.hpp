#ifndef CHARACTER_PLAYER_PLAYER_HPP_
#define CHARACTER_PLAYER_PLAYER_HPP_

#include <vector>
#include <utility>

#include "character/player/Graphics.hpp"
#include "character/player/Physics.hpp"
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

    enum class PowerLevel
    {
        Small,
        Big,
        Fireball
    };

    Player();

    virtual void on_simulate(double delta_time) override;
    virtual void draw(double delta_time) override;
    void on_input();
    void on_collision(Collision collision, Object& object);
    void setAnimationDelay(double delay);
    std::vector<Object::CollisionPoint> getCollisionPoints() override;

    bool on_ground_{false};
    bool crouched_{false};
    bool facing_left_{false};
    PowerLevel power_level{PowerLevel::Small};
    PowerLevel previous_power_level{PowerLevel::Small};
    State state{State::Standing};
    State previousState{State::Standing};

protected:
    Graphics graphics_;
    Physics physics_;
};

}  // namespace player
}  // namespace character

#endif  // CHARACTER_PLAYER_PLAYER_HPP_
