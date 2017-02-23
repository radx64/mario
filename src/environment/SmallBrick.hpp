#ifndef ENVIRONMENT_SMALLBRICK_HPP_
#define ENVIRONMENT_SMALLBRICK_HPP_

#include "Object.hpp"
#include "Bitmap.hpp"

#include "math/Vector2.hpp"

class AnimatedBitmap;

namespace environment
{

class SmallBrick : public Object
{
public:
    SmallBrick(math::Vector2f initialPosition, math::Vector2f velocity);

    virtual void draw() override;
    virtual void update(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    AnimatedBitmap* bitmap_;

    math::Vector2f velocity_;
};

}  // namespace environment

#endif  // ENVIRONMENT_SMALLBRICK_HPP_
