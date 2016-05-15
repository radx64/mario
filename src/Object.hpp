#ifndef OBJECT_HPP_
#define OBJECT_HPP_

class Context;

class Object
{
public:
    Object(Context& context, int type);

    virtual void draw();
    virtual void simulate();
    virtual void checkCollision(Object& different);

    int x;
    int y;
    int w;
    int h;


private:
    Context& context_;
    int type_;
    int r_;
    int g_;
    int b_;
};

#endif  //OBJECT_HPP_
