#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <cstdint>

class Camera
{
public:
    void setX(int32_t x);
    void setY(int32_t y);

    int32_t getX();
    int32_t getY();

private:
    int32_t x_;
    int32_t y_;
};

#endif  // CAMERA_HPP_
