#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <vector> 

class Object;

struct Level
{
    std::vector<Object*> objects;
    std::vector<Object*> toSpawnObjects;
};

class World
{
public:
    int8_t coins_{0};
    int8_t lives_{0};
    Level level;
};

#endif  // WORLD_HPP_
