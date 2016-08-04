#ifndef CHARACTER_PLAYERGRAPHICSCOMPONENT_HPP_
#define CHARACTER_PLAYERGRAPHICSCOMPONENT_HPP_

#include <vector>

class AnimatedBitmap;
class Context;

namespace character
{
class Player;

class PlayerGraphicsComponent
{
public:
    PlayerGraphicsComponent(Player& player, Context& context);
    ~PlayerGraphicsComponent();
    void draw();

protected:
    Context& context_;
    Player& player_;

    AnimatedBitmap* runningAnimation_;
    AnimatedBitmap* standingAnimation_;
    AnimatedBitmap* jumpAnimation_;
    AnimatedBitmap* currentAnimation_;
    std::vector<std::pair<int,int>> debugFrames_;
};

}  // namespace character

#endif  // CHARACTER_PLAYERGRAPHICSCOMPONENT_HPP_
