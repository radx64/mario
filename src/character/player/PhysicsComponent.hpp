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
    void input();
    void on_collision(Collision collision, Object& object);

protected:
    inline void bounce_of_ceiling();
    inline void jump();
    inline void move_left(float& horizontalAcceleration);
    inline void move_right(float& horizontalAcceleration);

    inline float get_max_running_speed(bool running);

    Player& player_;

    const float grav_ {600.0};
    const float max_walk_speed_ {100.0};
    const float max_run_speed_ {150.0};
    uint32_t fireCooldown {0};
    float horizontalAcceleration{};
};

}  // namespace player
}  // namespace character

#endif  // CHARACTER_PLAYER_PHYSICSSCOMPONENT_HPP_
