#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>

struct Collision
{
    bool left;
    bool right;
    bool top;
    bool bottom;

    bool hasCollided()
    {
        return left || right || top || bottom;
    }

    Collision opposite()
    {
        return Collision{right, left, bottom, top};
    }
};


class Object
{
public:
    Object(int type);

    virtual void draw() = 0;
    virtual void simulate(std::vector<Object*> gameObjects);
    virtual void onCollisionWith(Collision collision, Object& object) = 0;

    double x{};
    double y{};
    int w{};
    int h{};

    float dx{};
    float dy{};

    int type_{};

protected:


    virtual Collision checkCollision(Object& different);
};

#endif  //OBJECT_HPP_
