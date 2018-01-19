#ifndef CHARACTER_PLAYER_GRAPHICSCOMPONENT_HPP_
#define CHARACTER_PLAYER_GRAPHICSCOMPONENT_HPP_

class AnimatedSprite;

namespace character
{
namespace player
{

class Player;

class GraphicsComponent
{
public:
    GraphicsComponent(Player& player);
    void draw();
    void setDelay(short speed);

protected:
    Player& player_;

    AnimatedSprite* runningAnimation_;
    AnimatedSprite* standingAnimation_;
    AnimatedSprite* slideAnimation_;
    AnimatedSprite* jumpAnimation_;
    AnimatedSprite* currentAnimation_;
};

}  // namespace player
}  // namespace character

#endif  // CHARACTER_PLAYER_GRAPHICSCOMPONENT_HPP_
