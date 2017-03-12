#ifndef CHARACTER_GOOMBA_GOOMBA_HPP
#define CHARACTER_GOOMBA_GOOMBA_HPP

#include <memory>

#include "Object.hpp"

class AnimatedSprite;

namespace character
{
namespace goomba
{

class Goomba : public Object
{
public:
    Goomba();

    virtual void draw() override;
    virtual void onUpdate(std::vector<Object*> gameObjects, double timeStep) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:

    enum class State
    {
        Walking,
        Dying
    };

    AnimatedSprite* walking_;
    AnimatedSprite* squashed_;
    AnimatedSprite* currentAnimation_;
    State state_{State::Walking};
    const float grav_ {5.0};
    uint8_t dyingCounter_{0};
};

}  // namespace goomba
}  // namespace character

#endif  // CHARACTER_GOOMBA_GOOMBA_HPP
