#include "Object.hpp"

#include <cstdlib>

Object::Object(int type) : type_(type)
{
}

bool Object::checkCollision(Object& different)
{
    return (abs(x + dx - different.x) < (w + different.w) / 2) &&
        (abs(y + dy - different.y) < (h + different.h) / 2);

}
