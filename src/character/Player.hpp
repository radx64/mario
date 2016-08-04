#ifndef CHARACTER_PLAYER_HPP_
#define CHARACTER_PLAYER_HPP_

#include <vector>
#include <utility>

#include "Object.hpp"
#include "AnimatedBitmap.hpp"

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

class Player : public Object
{
public:
    Player(Context& context, int type);
    virtual void update(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;
    bool jumped_{false};

protected:
    virtual void draw();
    bool isObjectAt(std::vector<Object*> gameObjects, float x, float y);
    void bouceOfCeiling(Object* ceilingBlock);
    Context& context_;
    PlayerGraphicsComponent graphics_;

    const float grav_ {0.28};
    const float horizontalMaxSpeed_ {7.0};
};

}  // namespace character

#endif  // CHARACTER_PLAYER_HPP_
