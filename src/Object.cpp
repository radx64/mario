#include "Object.hpp"

#include <cmath>

#include <iostream>

Object::Object(int type) : type_(type)
{
}

Object::~Object()
{
}

void Object::update(std::vector<Object*> gameObjects)
{
    for (auto object : gameObjects)
    {
        if (object == this) continue; // skip collision with itself

        auto col = checkCollision(*object);

        if (col.hasCollided())
        {
            onCollisionWith(col, *object);

            object->onCollisionWith(col.opposite(), *this);
        }

    }
}

Collision Object::checkCollision(Object& collider)
{
    math::Vector2f distance = collider.position - position;

    if (!(position.x < collider.position.x + collider.size.x &&
       position.x + size.x > collider.position.x &&
       position.y < collider.position.y + collider.size.y &&
       size.y + position.y > collider.position.y))
    {
        return Collision(Collision::State::None);
    }

    const float sideCollisionThreshold {3.0}; // because side collisions are more important

    if (fabs(distance.y) <  fabs(distance.x) + sideCollisionThreshold)
    {
        if (position.x <= collider.position.x) return Collision(Collision::State::Right);
        else return Collision(Collision::State::Left);
    }
    else
    {
        if (position.y+size.y/2 <= collider.position.y) return Collision(Collision::State::Bottom);
        else return Collision(Collision::State::Top);
    }

}
