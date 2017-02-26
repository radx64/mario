#ifndef CHARACTER_PLAYER_GRAPHICSCOMPONENT_HPP_
#define CHARACTER_PLAYER_GRAPHICSCOMPONENT_HPP_

class AnimatedBitmap;

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
    void setSpeed(short speed);

protected:
    Player& player_;

    AnimatedBitmap* runningAnimation_;
    AnimatedBitmap* standingAnimation_;
    AnimatedBitmap* slideAnimation_;
    AnimatedBitmap* jumpAnimation_;
    AnimatedBitmap* currentAnimation_;
};

}  // namespace player
}  // namespace character

#endif  // CHARACTER_PLAYER_GRAPHICSCOMPONENT_HPP_
