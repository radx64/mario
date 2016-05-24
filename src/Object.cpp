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
    float predictedX = x + dx;
    float predictedY = y + dy;

    float distanceX = fabs(collider.x - predictedX);
    float distanceY = fabs(collider.y - predictedY);

    float maxWidth = std::max(w, collider.w);
    float maxHeight = std::max(h, collider.h);

    float minWidth = std::min(w, collider.w);
    float minHeight = std::min(h, collider.h); 

    Collision col{false, false, false, false};

    bool horizontalIntersection = false;
    bool verticalIntersection = false;

    (void)maxHeight;

    if (y < collider.y) verticalIntersection = (distanceY < maxHeight);
        else verticalIntersection = (distanceY < minHeight);

    if (x < collider.x) horizontalIntersection = (distanceX < maxWidth);
        else horizontalIntersection = (distanceX < minWidth);

    if (!(horizontalIntersection && verticalIntersection))
    {
        return col;
    }

    float angle = atan2(y - collider.y,
                        x - collider.x);

    angle = angle * 180.0 / M_PI;

    if ( angle > -35.0 && angle < 35.0) col.left = true;
    if ( angle > 145.0 || angle < -145.0) col.right = true;
    if ( angle > 45.0 && angle < 135.0) col.top = true;
    if ( angle > -135.0 && angle < -45.0) col.bottom = true;

    return col;

}
