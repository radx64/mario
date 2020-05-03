#include "Object.hpp"

#include "Context.hpp"

#include <cmath>

#include <iostream>
#include <SDL2/SDL.h>

Object::Object(ObjectType type) : type_(type)
{
}

void Object::simulate(double timeStep)
{
    lifetime_ += timeStep;
    on_simulate(timeStep);
}

void Object::collide(std::vector<Object*> gameObjects)
{
    find_collisions(gameObjects);
}

std::vector<Object::CollisionPoint> Object::getCollisionPoints()
{
        return std::vector<CollisionPoint> {
        {Collision::State::Bottom, {position.x + size.x*1.0f/8.0f,  position.y + size.y-1}},
        {Collision::State::Bottom, {position.x + size.x*7.0f/8.0f,  position.y + size.y-1}},
        {Collision::State::Top,    {position.x + size.x/2.0f,       position.y}},
        {Collision::State::Left,   {position.x ,                    position.y + size.y*1.0f/3.0f}},
        {Collision::State::Left,   {position.x ,                    position.y + size.y*2.0f/3.0f}},
        {Collision::State::Right,  {position.x + size.x,            position.y + size.y*1.0f/3.0f}},
        {Collision::State::Right,  {position.x + size.x,            position.y + size.y*2.0f/3.0f}},
    };
}

void Object::find_collisions(std::vector<Object*> collidableObjects)
{
    if (!moving) return;
    
    std::vector<CollisionPoint> collisionsPoints = getCollisionPoints();

    for(auto collisionPoint : collisionsPoints)
    {
        auto colliders = getObjectsAt(collidableObjects, collisionPoint.point);
        if (colliders.empty()) continue;

        for (Object* collider : colliders)
        {
            Collision collision {collisionPoint.collision};
            on_collision(collision, *collider);
            collider->on_collision(collision.opposite(), *this);
        }
    }
}

std::vector<Object*> Object::getObjectsAt(std::vector<Object*> gameObjects, math::Vector2f point)
{
    std::vector<Object*> result;

    for(auto object : gameObjects)  // this is not an optimal way to check collsions
    {                               // spatial cheking maybe divided to smaller sectors or something
        if (object != this && // no collsion with self
            object->collidable &&
            (point.x > object->position.x && point.x < object->position.x + object->size.x) &&
            (point.y > object->position.y && point.y < object->position.y + object->size.y)) 

        {
            result.push_back(object);
        }
    }
    return result;
}
