#ifndef ENVIRONMENT_BACKGROUND_HPP_
#define ENVIRONMENT_BACKGROUND_HPP_

#include <memory>

#include "Object.hpp"
#include "BitmapsContainer.hpp"
#include "Sprite.hpp"

namespace environment
{

class Background : public Object
{
public:
    Background(SpriteType bitmap);
    
    virtual void draw() override;
    virtual void onUpdate(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    Sprite* sprite_;
};

}  // namespace environment

#endif  // ENVIRONMENT_BACKGROUND_HPP_
