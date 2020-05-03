#ifndef CHARACTER_PLAYER_PHYSICSSCOMPONENT_HPP_
#define CHARACTER_PLAYER_PHYSICSSCOMPONENT_HPP_

#include <vector>

#include "Collision.hpp"

class AnimatedBitmap;
class Object;
class KeyboardState;

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
    void input();
    void on_collision(Collision collision, Object& object);

protected:
    inline void bounce_of_ceiling();
    inline void jump();
    inline void move_sideways(KeyboardState* keys);

    inline double get_max_running_speed(bool running);

    Player& player_;

    const double max_walk_speed_ {100.0};
    const double max_run_speed_ {200.0};
    uint32_t fireCooldown {0};
    double horizontalAcceleration{};
    double verticalAcceleration{};
};

}  // namespace player
}  // namespace character

#endif  // CHARACTER_PLAYER_PHYSICSSCOMPONENT_HPP_
