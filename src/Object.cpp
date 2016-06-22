#include "Object.hpp"

#include <cmath>

#include <iostream>

Object::Object(int type) : type_(type)
{
}

void Object::simulate(std::vector<Object*> gameObjects)
{
    for (auto object : gameObjects)
    {
        if (object == this) continue; // skip collision with itself

        auto col = checkCollision(*object);

        if (col.hasCollided())
        {
            onCollisionWith(col, *object);

            object->onCollisionWith(col.opposite(), *this);
        }

    }
}

Collision Object::checkCollision(Object& collider)
{
    float distanceX = fabs(collider.x - x);
    float distanceY = fabs(collider.y - y);

    if (!(x < collider.x + collider.w &&
       x + w > collider.x &&
       y < collider.y + collider.h &&
       h + y > collider.y))
    {
        return {false,false,false,false};
    }

    if (distanceY <  distanceX)
    {
        if (x < collider.x) return{false,true,false,false};
        else return{true,false,false,false};
    }
    else
    {
        if (y < collider.y) return{false,false,false,true};
        else return{false,false,true,false};
    }


    return {false,false,false,false};

}
