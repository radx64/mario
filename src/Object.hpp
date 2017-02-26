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
    virtual void draw() = 0;
    virtual void onCollisionWith(Collision collision, Object& object) = 0;

    math::Vector2f position;
    math::Vector2f velocity;  
    math::Vector2f size;

    bool collidable {false};  
        // this will make collsions calculations faster (now info is staticaly initialized
        // in constructor but can be dynamically calculated later)
        // some objects shouldn't be collidable (little bricks, dead bodies, etc)

    bool moving {false};
        // if object is not moving there is no point to check by it is it colliding with anything
        // long story short - only moving objects are checking collisions with collidable objects.


    bool dead{false};

    int type_{};  // this will be removed later, temporary hack for object detection

protected:
    Object* getObjectAt(std::vector<Object*> gameObjects, math::Vector2f point);

    struct CollisionPoint
    {
        Collision collision;
        math::Vector2f point;
    };
};

#endif  //OBJECT_HPP_
