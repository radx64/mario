#include "BitmapsContainer.hpp"

#include "Bitmap.hpp"

#include <iostream>
#include <stdexcept>

BitmapsContainer::BitmapsContainer(SDL_Renderer* renderer,
    std::map<BitmapType, std::string> bitmapFiles)
{
    for (const auto& entity : bitmapFiles)
    {
        std::shared_ptr<Bitmap> bitmap = std::make_shared<Bitmap>(renderer, entity.second);
        items_[entity.first] = bitmap;

        std::cout << "Loading bitmap " << entity.second << std::endl;
    }
}

std::shared_ptr<Bitmap> BitmapsContainer::get(BitmapType type)
{
    try
    {
        return items_.at(type);
    }
    catch (std::out_of_range e)
    {
        std::cout << "Requested element is not in container" << std::endl;
    }
    return std::shared_ptr<Bitmap>();
}
