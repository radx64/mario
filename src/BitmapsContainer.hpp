#ifndef BITMAPS_CONTAINER_HPP_
#define BITMAPS_CONTAINER_HPP_

#include <map>
#include <string>

#include "SpriteType.hpp"

class SDL_Renderer;
class Sprite;

class BitmapsContainer
{
public:
    BitmapsContainer(std::map<SpriteType, std::string> bitmapFiles);
    ~BitmapsContainer();
    Sprite* get(SpriteType type);

private:
   std::map<SpriteType, Sprite*> items_;
};

#endif  // BITMAPS_CONTAINER_HPP_
