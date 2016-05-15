#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>

class Object
{
public:
    Object(int type);

    virtual void draw() = 0;
    virtual void simulate(std::vector<Object*> gameObjects) = 0;

    int x{};
    int y{};
    int w{};
    int h{};

    float dx{};
    float dy{};

    int type_{};

protected:
    virtual bool checkCollision(Object& different);
};

#endif  //OBJECT_HPP_
