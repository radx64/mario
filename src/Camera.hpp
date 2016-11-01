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

    void setW(int32_t x);
    void setH(int32_t y);
    int32_t getW();
    int32_t getH();


private:
    int32_t x_;
    int32_t y_;
    int32_t w_;
    int32_t h_;
};

#endif  // CAMERA_HPP_
