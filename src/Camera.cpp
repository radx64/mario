#include "Camera.hpp"

void Camera::setX(int32_t x)
{
    x_ = x - 240;
}

void Camera::setY(int32_t y)
{
    (void) y;
    y_= 0;
}

int32_t Camera::getX()
{
    return x_;
}

int32_t Camera::getY()
{
    return y_;
}

