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

    float avgWidth = (w + collider.w) / 2.0;
    float avgHeight = (h + collider.h) / 2.0;

    Collision col{false, false, false, false};

    bool horizontalIntersection = (distanceX < avgWidth);
    bool verticalIntersection = (distnaceY < avgHeight);

    if (!(horizontalIntersection && verticalIntersection))
    {
        return col;
    }

    float angle = atan2(y - collider.y,
                        x - collider.x);

    angle = angle * 180.0 / M_PI;

    std::cout << "Angle: " << angle << std::endl;

    if ( angle > -45.0 && angle < 45.0) col.left = true;
    if ( angle > 45.0 && angle < 135.0) col.top = true;

    if ( angle > -135.0 && angle < -45.0) col.bottom = true;
    if ( angle > 135.0 || angle < -135.0) col.right = true;

    return col;

}

// Object::Collision Object::checkCollision(Object& collider)
// {
//     bool collided = (fabs(x + dx - collider.x) < (w + collider.w) / 2) &&
//         (fabs(y + dy - collider.y) < (h + collider.h) / 2);

//     Collision col{false, false, false, false};

//     if (!collided) return col;

//     if (y < collider.y ) col.bottom = true;
//     if (y > collider.y ) col.top = true;

//     if (x < collider.x && y != collider.y) col.right = true;
//     if (x > collider.x && y != collider.y) col.left = true;

//     return col;

// }
