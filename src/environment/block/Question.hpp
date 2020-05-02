#ifndef ENVIRONMENT_BLOCK_QUESTION_HPP_
#define ENVIRONMENT_BLOCK_QUESTION_HPP_

#include <memory>

#include "math/Vector2.hpp"
#include "Object.hpp"

class AnimatedSprite;

namespace environment
{
namespace block
{

class Question : public Object
{
public:
    Question(math::Vector2f position);

    virtual void draw(double delta_time) override;
    virtual void onUpdate(std::vector<Object*> gameObjects, double timeStep) override;
    virtual void onCollisionWith(Collision collision, Object& object) = 0;

protected:
    AnimatedSprite* fullAnimation_;
    AnimatedSprite* depletedAnimation_;
    AnimatedSprite* currentAnimation_;
    bool depleted_{false};
    bool bounce_{false};
    double bounceTick_{0};
    math::Vector2f originalPosition{};
};



}  // namespace block
}  // namespace environment

#endif  // ENVIRONMENT_BLOCK_QUESTION_HPP_
