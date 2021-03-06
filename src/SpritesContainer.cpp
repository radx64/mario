#include "SpritesContainer.hpp"

#include <iostream>
#include <stdexcept>

#include "Sprite.hpp"

SpritesContainer::SpritesContainer(std::map<SpriteType, std::string> bitmapFiles)
{
    for (const auto& entity : bitmapFiles)
    {
        Sprite* sprite = new Sprite(entity.second);
        items_[entity.first] = sprite;

        std::cout << "Loading sprite " << entity.second << std::endl;
    }
}

SpritesContainer::~SpritesContainer()
{
    for (auto spritePair: items_)
    {   
        delete spritePair.second;
    }
}


Sprite* SpritesContainer::get(SpriteType type)
{
    try
    {
        return items_.at(type);
    }
    catch (std::out_of_range e)
    {
        std::cout << "Requested sprite is not in container" << std::endl;
    }
    return nullptr;
}
