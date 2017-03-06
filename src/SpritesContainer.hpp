#ifndef SPRITES_CONTAINER_HPP_
#define SPRITES_CONTAINER_HPP_

#include <map>
#include <string>

#include "SpriteType.hpp"

class SDL_Renderer;
class Sprite;

class SpritesContainer
{
public:
    SpritesContainer(std::map<SpriteType, std::string> bitmapFiles);
    ~SpritesContainer();
    Sprite* get(SpriteType type);

private:
   std::map<SpriteType, Sprite*> items_;
};

#endif  // SPRITES_CONTAINER_HPP_
