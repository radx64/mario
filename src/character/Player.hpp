#ifndef CHARACTER_PLAYER_HPP_
#define CHARACTER_PLAYER_HPP_

#include "Object.hpp"
#include "AnimatedBitmap.hpp"

class Context;

namespace character
{

class Player : public Object
{
public:
    Player(Context& context, int type);
    ~Player();

    virtual void draw() override;
    virtual void simulate(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    bool isObjectAt(std::vector<Object*> gameObjects, float x, float y);
    void bouceOfCeiling(Object* ceilingBlock);
    int r_{};
    int g_{};
    int b_{};
    bool jumped_{false};
    Context& context_;
    AnimatedBitmap* bitmap_;
    const float grav_ {0.28};
    const float horizontalMaxSpeed_ {7.0};
};

}  // namespace character

#endif  // CHARACTER_PLAYER_HPP_
