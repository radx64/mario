#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>

#include "Collision.hpp"



class Object
{
public:
    Object(int type);
    virtual ~Object();
    virtual void update(std::vector<Object*> gameObjects);
    virtual void onCollisionWith(Collision collision, Object& object) = 0;

    double x{};
    double y{};
    int w{};
    int h{};

    double ax{};
    double ay{};

    bool dead {false};

    int type_{};

protected:

    virtual Collision checkCollision(Object& different);
};

#endif  //OBJECT_HPP_
