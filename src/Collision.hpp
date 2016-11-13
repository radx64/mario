#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include <string>

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

    std::string toString()
    {
        switch(state_)
        {
            case State::Left   : return "Left";
            case State::Right  : return "Right";
            case State::Top    : return "Top";
            case State::Bottom : return "Bottom";
            default            : return "None";
        }        
    }

    State get()
    {
        return state_;
    }

private:
    State state_;
};

#endif  //COLLISION_HPP_
