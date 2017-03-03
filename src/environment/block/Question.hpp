#ifndef ENVIRONMENT_BLOCK_QUESTION_HPP_
#define ENVIRONMENT_BLOCK_QUESTION_HPP_

#include <memory>

#include "math/Vector2.hpp"
#include "Object.hpp"

class AnimatedBitmap;

namespace environment
{
namespace block
{

class Question : public Object
{
public:
    Question(math::Vector2f position);

    virtual void draw() override;
    virtual void onUpdate(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) = 0;

protected:
    AnimatedBitmap* fullAnimation_;
    AnimatedBitmap* depletedAnimation_;
    AnimatedBitmap* currentAnimation_;
    bool depleted_{false};
    bool bounce_{false};
    int8_t bounceTick_{0};
    math::Vector2f originalPosition{};
};

class Coins : public Question
{
public:
    Coins(math::Vector2f position, uint8_t coins);
    virtual void onCollisionWith(Collision collision, Object& object) override;

private:
    int8_t coins_;
};

class Mushroom : public Question
{
public:
    Mushroom(math::Vector2f position);
    virtual void onCollisionWith(Collision collision, Object& object) override;
};

}  // namespace block
}  // namespace environment

#endif  // ENVIRONMENT_BLOCK_QUESTION_HPP_
