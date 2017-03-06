#include "BitmapsContainer.hpp"

#include <iostream>
#include <stdexcept>

#include "Sprite.hpp"

BitmapsContainer::BitmapsContainer(std::map<SpriteType, std::string> bitmapFiles)
{
    for (const auto& entity : bitmapFiles)
    {
        Sprite* sprite = new Sprite(entity.second);
        items_[entity.first] = sprite;

        std::cout << "Loading sprite " << entity.second << std::endl;
    }
}

BitmapsContainer::~BitmapsContainer()
{
    for (auto spritePair: items_)
    {   
        delete spritePair.second;
    }
}


Sprite* BitmapsContainer::get(SpriteType type)
{
    try
    {
        return items_.at(type);
    }
    catch (std::out_of_range e)
    {
        std::cout << "Requested element is not in container" << std::endl;
    }
    return nullptr;
}
