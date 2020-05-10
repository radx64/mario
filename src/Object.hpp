#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>
#include "math/Vector2.hpp"
#include "ObjectType.hpp"
#include "Collision.hpp"

class Object
{
public:
    Object(ObjectType type);
    virtual ~Object() = default;
    void simulate(double delta_time);
    void collide(std::vector<Object*> gameObjects);

    virtual void draw(double delta_time) = 0;

    virtual void on_collision(Collision collision, Object& object) = 0;

    math::Vector2f position;
    math::Vector2f velocity;
    math::Vector2f size;

    /**
        this will make collsions calculations faster (now info is staticaly initialized
        in constructor but can be dynamically calculated later)
        some objects shouldn't be collidable (little bricks, dead bodies, etc)
    **/
    bool collidable_ {false};

    /**
        if object is not moving there is no point to check by it is it colliding with anything
        long story short - only moving objects are checking collisions with collidable objects.
    **/
    bool moving_ {false};

    /**
        used for dead bodies cleanup
    **/
    bool dead_ {false};

    ObjectType type_{};


protected:
    struct CollisionPoint
    {
        Collision collision;
        math::Vector2f point;
    };
    /**
        this method may be overloaded by derived class to define own colision points still working with base findCollsions method
    **/
    virtual std::vector<CollisionPoint> getCollisionPoints();
    virtual void on_simulate(double timeStep) = 0;
    void find_collisions(std::vector<Object*> gameObjects);
    std::vector<Object*> getObjectsAt(std::vector<Object*> gameObjects, math::Vector2f point);

    double lifetime_{};
};

#endif  //OBJECT_HPP_
