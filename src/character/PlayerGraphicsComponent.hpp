#ifndef CHARACTER_PLAYERGRAPHICSCOMPONENT_HPP_
#define CHARACTER_PLAYERGRAPHICSCOMPONENT_HPP_

#include <vector>

class AnimatedBitmap;

namespace character
{
class Player;

class PlayerGraphicsComponent
{
public:
    PlayerGraphicsComponent(Player& player);
    ~PlayerGraphicsComponent();
    void draw();
    void setSpeed(short speed);

protected:
    Player& player_;

    AnimatedBitmap* runningAnimation_;
    AnimatedBitmap* standingAnimation_;
    AnimatedBitmap* slideAnimation_;
    AnimatedBitmap* jumpAnimation_;
    AnimatedBitmap* currentAnimation_;
    std::vector<std::pair<int,int>> debugFrames_;
};

}  // namespace character

#endif  // CHARACTER_PLAYERGRAPHICSCOMPONENT_HPP_
