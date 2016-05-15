#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>

class Object
{
public:
    Object(int type);

    virtual void draw() = 0;
    virtual void simulate(std::vector<Object*> gameObjects) = 0;

    double x{};
    double y{};
    int w{};
    int h{};

    float dx{};
    float dy{};

    int type_{};

protected:
    struct Collision
    {
        bool left;
        bool right;
        bool top;
        bool bottom;
    };

    virtual Collision checkCollision(Object& different);
};

#endif  //OBJECT_HPP_
