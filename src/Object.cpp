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
    if (!moving)
    {
        return;  // there is no sense for checking collison when object is not moving
    }

    std::vector<CollisionPoint> collisionsPoints{
        {Collision::State::Bottom, {position.x + size.x/2.0, position.y+size.y-1.0}},
        {Collision::State::Top,    {position.x + size.x/2.0, position.y}},
        {Collision::State::Left,   {position.x , position.y + size.y/2.0}},
        {Collision::State::Right,  {position.x + size.x-1.0, position.y + size.y/2.0}},
    };

    for(auto collisionPoint : collisionsPoints)
    {
        auto collider = getObjectAt(gameObjects, collisionPoint.point);
        if (collider)
        {
            Collision collision {collisionPoint.collision};
            onCollisionWith(collision, *collider);
            collider->onCollisionWith(collision.opposite(), *this);
        }
    }
}

Object* Object::getObjectAt(std::vector<Object*> gameObjects, math::Vector2f point)
{
    for(auto object : gameObjects)  // this is not an optimal way to check collsions
    {                               // spatial cheking maybe divided to smaller sectors or something
        if (object != this &&
            (point.x > object->position.x && point.x < object->position.x + object->size.x) &&
            (point.y > object->position.y && point.y < object->position.y + object->size.y)
            ) // no collsion with self
        {
            return object;
        }
    }
    return nullptr;
}
