#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>

class Collision
{
public:
    enum class State
    {
        None,
        Left,
        Right,
        Top,
        Bottom
    };

    Collision(State state) : state_{state}{}

    bool hasCollided()
    {
        return state_ != State::None;
    }

    Collision opposite()
    {
        switch(state_)
        {
            case State::Left   : return Collision{State::Right};
            case State::Right  : return Collision{State::Left};
            case State::Top    : return Collision{State::Bottom};
            case State::Bottom : return Collision{State::Top};
            default            : return Collision {State::None};
        }
    }

    State get()
    {
        return state_;
    }

private:
    State state_;
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

    double ax{};
    double ay{};

    int type_{};

protected:

    virtual Collision checkCollision(Object& different);
};

#endif  //OBJECT_HPP_
