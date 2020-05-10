#ifndef CHARACTER_PLAYER_GRAPHICSCOMPONENT_HPP_
#define CHARACTER_PLAYER_GRAPHICSCOMPONENT_HPP_

#include <unordered_map>

#include <SpriteType.hpp>

class AnimatedSprite;

namespace character
{
namespace player
{

class Player;

class Graphics
{
public:
    Graphics(Player& player);
    void draw(double delta_time);
    void setDelay(double speed);

protected:
    Player& player_;

    enum class Animation
    {
        Big_Running,
        Big_Standing,
        Big_Sliding,
        Big_Jumping,
        Big_Crouching,
        Small_Running,
        Small_Standing,
        Small_Sliding,
        Small_Jumping,
    };

    std::unordered_map<Animation, AnimatedSprite*> animations_;
    AnimatedSprite* currentAnimation_;
};

}  // namespace player
}  // namespace character

#endif  // CHARACTER_PLAYER_GRAPHICSCOMPONENT_HPP_
