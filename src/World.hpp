#ifndef WORLD_HPP_
#define WORLD_HPP_

class Object;

class World
{
public:
    int8_t coins_{0};
    int8_t lives_{0};
    std::vector<Object*> gameObjects_;
};

#endif  // WORLD_HPP_
