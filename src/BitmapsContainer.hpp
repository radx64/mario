#ifndef BITMAPS_CONTAINER_HPP_
#define BITMAPS_CONTAINER_HPP_

#include <map>
#include <memory>
#include <string>

class Bitmap;
class SDL_Renderer;

enum class BitmapType
{
    BRICK_RED,
    GROUND_RED,
    MARIO_JUMPING,
    MARIO_RUNNING_0,
    MARIO_RUNNING_1,
    MARIO_RUNNING_2,
    MARIO_STANDING,
    QUESTIONBLOCK_0,
    QUESTIONBLOCK_1,
    QUESTIONBLOCK_2
};

class BitmapsContainer
{
public:
    BitmapsContainer(SDL_Renderer* renderer, std::map<BitmapType, std::string> bitmapFiles);
    std::shared_ptr<Bitmap> get(BitmapType type);

private:
   std::map<BitmapType, std::shared_ptr<Bitmap>> items_; 
};

#endif  // BITMAPS_CONTAINER_HPP_
