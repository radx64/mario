#ifndef COLLISION_HPP_
#define COLLISION_HPP_

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

#endif  //COLLISION_HPP_
