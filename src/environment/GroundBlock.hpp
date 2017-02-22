#ifndef ENVIRONMENT_GROUNDBLOCK_HPP_
#define ENVIRONMENT_GROUNDBLOCK_HPP_

#include "Object.hpp"
#include "Bitmap.hpp"
#include <memory>

class Context;

namespace environment
{

class GroundBlock : public Object
{
public:
    GroundBlock(int type);

    virtual void draw() override;
    virtual void update(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    std::shared_ptr<Bitmap> bitmap_;
};

}  // namespace environment

#endif  // ENVIRONMENT_GROUNDBLOCK_HPP_
