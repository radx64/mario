#ifndef ENVIRONMENT_MUSHROOM_HPP
#define ENVIRONMENT_MUSHROOM_HPP

#include <memory>
#include <vector>

#include "Bitmap.hpp"
#include "Object.hpp"

namespace environment
{

class Mushroom : public Object
{
public:
    Mushroom();

    virtual void draw() override;
    virtual void onUpdate(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    std::shared_ptr<Bitmap> bitmap_;
    const float grav_ {0.20};
};

}  // namespace environment

#endif  // ENVIRONMENT_MUSHROOM_HPP
