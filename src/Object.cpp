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

    auto collider = getObjectAt(gameObjects, {position.x + size.x/2.0, position.y+size.y-1.0});

    if (collider)
    {
        Collision collision {Collision::State::Bottom};
        onCollisionWith(collision, *collider);
        collider->onCollisionWith(collision.opposite(), *this);
    }

    collider = getObjectAt(gameObjects, {position.x + size.x/2.0, position.y});

    if (collider)
    {
        Collision collision {Collision::State::Top};
        onCollisionWith(collision, *collider);
        collider->onCollisionWith(collision.opposite(), *this);
    }

    collider = getObjectAt(gameObjects, {position.x , position.y + size.y/2.0});

    if (collider)
    {
        Collision collision {Collision::State::Left};
        onCollisionWith(collision, *collider);
        collider->onCollisionWith(collision.opposite(), *this);
    }

    collider = getObjectAt(gameObjects, {position.x + size.x-1.0, position.y + size.y/2.0});

    if (collider)
    {
        Collision collision {Collision::State::Right};
        onCollisionWith(collision, *collider);
        collider->onCollisionWith(collision.opposite(), *this);
    }

}

Object* Object::getObjectAt(std::vector<Object*> gameObjects, math::Vector2f point)
{
    for(auto object : gameObjects)  // this is not an optimal way to check collsions
    {                               // spatial cheking maybe divided to smaller sectors or something
        if ((point.x > object->position.x && point.x < object->position.x + object->size.x) &&
            (point.y > object->position.y && point.y < object->position.y + object->size.y) &&
            object != this) // no collsion with self
        {
            return object;
        }
    }
    return nullptr;
}
