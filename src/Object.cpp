#include "Object.hpp"

#include <cmath>

#include <iostream>

Object::Object(ObjectType type) : type_(type)
{
}

Object::~Object()
{
}

void Object::update(std::vector<Object*> gameObjects)
{
    ++lifetime_;
    onUpdate(gameObjects);
}

void Object::findCollisions(std::vector<Object*> collidableObjects)
{
    if (!moving) return;
    std::vector<CollisionPoint> collisionsPoints{
        {Collision::State::Bottom, {position.x + size.x*1.0f/4.0f,  position.y + size.y-1}},
        {Collision::State::Bottom, {position.x + size.x*3.0f/4.0f,  position.y + size.y-1}},
        {Collision::State::Top,    {position.x + size.x/2.0f,       position.y}},
        {Collision::State::Left,   {position.x ,                    position.y + size.y/2.0f}},
        {Collision::State::Right,  {position.x + size.x,            position.y + size.y/2.0f}},
    };

    for(auto collisionPoint : collisionsPoints)
    {
        auto collider = getObjectAt(collidableObjects, collisionPoint.point);
        if (!collider) continue;

        Collision collision {collisionPoint.collision};
        onCollisionWith(collision, *collider);
        collider->onCollisionWith(collision.opposite(), *this);
    }
}

Object* Object::getObjectAt(std::vector<Object*> gameObjects, math::Vector2f point)
{
    for(auto object : gameObjects)  // this is not an optimal way to check collsions
    {                               // spatial cheking maybe divided to smaller sectors or something
        if (object != this && // no collsion with self
            object->collidable &&
            (point.x > object->position.x && point.x < object->position.x + object->size.x) &&
            (point.y > object->position.y && point.y < object->position.y + object->size.y)) 

        {
            return object;
        }
    }
    return nullptr;
}
