#ifndef ENVIRONMENT_BACKGROUND_HPP_
#define ENVIRONMENT_BACKGROUND_HPP_

#include "Object.hpp"
#include "Bitmap.hpp"
#include "BitmapsContainer.hpp"
#include <memory>

namespace environment
{

class Background : public Object
{
public:
    Background(BitmapType bitmap);

    virtual void update(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    virtual void draw();
    std::shared_ptr<Bitmap> bitmap_;
};

}  // namespace environment

#endif  // ENVIRONMENT_BACKGROUND_HPP_
