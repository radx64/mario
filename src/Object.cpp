#include "Object.hpp"

#include <cmath>

#include <iostream>

Object::Object(int type) : type_(type)
{
}


Object::Collision Object::checkCollision(Object& collider)
{
    float predictedX = x + dx;
    float predictedY = y + dy;

    float distanceX = fabs(collider.x - predictedX);
    float distnaceY = fabs(collider.y - predictedY);

    float maxWidth = std::max(w, collider.w);
    float maxHeight = std::max(h, collider.h);

    Collision col{false, false, false, false};

    bool horizontalIntersection = (distanceX < maxWidth);
    bool verticalIntersection = (distnaceY < maxHeight);

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
