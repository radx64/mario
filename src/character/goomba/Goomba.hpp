#ifndef CHARACTER_GOOMBA_GOOMBA_HPP
#define CHARACTER_GOOMBA_GOOMBA_HPP

#include <memory>

#include "Object.hpp"

class AnimatedBitmap;

namespace character
{
namespace goomba
{

class Goomba : public Object
{
public:
    Goomba();

    virtual void draw() override;
    virtual void onUpdate(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:

    enum class State
    {
        Walking,
        Dying
    };

    AnimatedBitmap* walking_;
    AnimatedBitmap* squashed_;
    AnimatedBitmap* currentAnimation_;
    State state_{State::Walking};
    const float grav_ {0.20};
    uint8_t dyingCounter_{0};
};

}  // namespace goomba
}  // namespace character

#endif  // CHARACTER_GOOMBA_GOOMBA_HPP
