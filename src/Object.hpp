#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>
#include "math/Vector2.hpp"

#include "Collision.hpp"

class Object
{
public:
    Object(int type);
    virtual ~Object();
    virtual void update(std::vector<Object*> gameObjects);
    virtual void onCollisionWith(Collision collision, Object& object) = 0;

    math::Vector2f position;
    math::Vector2f velocity;  
    math::Vector2f size;

    bool dead {false};

    int type_{};  // this will be removed later, temporary hack for object detection

protected:

    Object* getObjectAt(std::vector<Object*> gameObjects, math::Vector2f point);

};

#endif  //OBJECT_HPP_
