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
    BUSH_LEFT,
    BUSH_MIDDLE,
    BUSH_RIGHT,
    GROUND_RED,
    HILL_LEFT,
    HILL_MIDDLE,
    HILL_MIDDLE_2,
    HILL_MIDDLE_3,
    HILL_RIGHT,
    HILL_TOP,
    MARIO_JUMPING,
    MARIO_RUNNING_0,
    MARIO_RUNNING_1,
    MARIO_RUNNING_2,
    MARIO_SLIDING,
    MARIO_STANDING,
    QUESTIONBLOCK_0,
    QUESTIONBLOCK_1,
    QUESTIONBLOCK_2,
    SQUID_0,
    SQUID_1,
    PIPE_TOP_LEFT,
    PIPE_TOP_RIGHT,
    PIPE_BOTTOM_LEFT,
    PIPE_BOTTOM_RIGHT
};

class BitmapsContainer
{
public:
    BitmapsContainer(std::map<BitmapType, std::string> bitmapFiles);
    std::shared_ptr<Bitmap> get(BitmapType type);

private:
   std::map<BitmapType, std::shared_ptr<Bitmap>> items_;
};

#endif  // BITMAPS_CONTAINER_HPP_
