#ifndef ANIMATED_BITMAP_HPP_
#define ANIMATED_BITMAP_HPP_

#include <list>
#include <string>
#include <memory>

#include "Bitmap.hpp"
#include "BitmapsContainer.hpp"

class SDL_Renderer;
class FlipFlags;

namespace graphics
{
    class IRenderer;
}

class AnimatedBitmap
{
public:
    AnimatedBitmap(std::list<BitmapType> bitmaps,
        short speed,
        BitmapsContainer& bitmapContainer);
    void draw(graphics::IRenderer* renderer, int x, int y);
    void draw(graphics::IRenderer* renderer, int x, int y, const FlipFlags& f);
    void nextFrame();

private:
    std::list<BitmapType> frames_;
    std::list<BitmapType>::iterator currentFrame_;
    BitmapsContainer& bitmapContainer_;
    short speed_;
    short currentFrameLifeTime_;
};


#endif  // ANIMATED_BITMAP_HPP_
