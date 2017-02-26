#ifndef BITMAPS_CONTAINER_HPP_
#define BITMAPS_CONTAINER_HPP_

#include <map>
#include <memory>
#include <string>

#include "BitmapType.hpp"

class Bitmap;
class SDL_Renderer;

class BitmapsContainer
{
public:
    BitmapsContainer(std::map<BitmapType, std::string> bitmapFiles);
    std::shared_ptr<Bitmap> get(BitmapType type);

private:
   std::map<BitmapType, std::shared_ptr<Bitmap>> items_;
};

#endif  // BITMAPS_CONTAINER_HPP_
