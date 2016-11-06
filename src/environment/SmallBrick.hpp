#ifndef ENVIRONMENT_SMALLBRICK_HPP_
#define ENVIRONMENT_SMALLBRICK_HPP_

#include "Object.hpp"
#include "Bitmap.hpp"
#include <memory>

class AnimatedBitmap;

namespace environment
{

class SmallBrick : public Object
{
public:
    SmallBrick(double ix, double iy, double x_velocity, double y_velocity);

    virtual void update(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    virtual void draw();

    AnimatedBitmap* bitmap_;

    double x_velocity_;
    double y_velocity_;
};

}  // namespace environment

#endif  // ENVIRONMENT_SMALLBRICK_HPP_
