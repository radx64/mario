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

void Camera::setW(int32_t w)
{
    w_ = w;
}

void Camera::setH(int32_t h)
{
    h_= h;
}

int32_t Camera::getW()
{
    return w_;
}

int32_t Camera::getH()
{
    return h_;
}

