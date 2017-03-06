#ifndef ANIMATED_BITMAP_HPP_
#define ANIMATED_BITMAP_HPP_

#include <list>
#include <string>
#include <memory>

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
    AnimatedBitmap(std::list<SpriteType> bitmaps,
        short speed,
        BitmapsContainer& bitmapContainer);
    void draw(graphics::IRenderer* renderer, int x, int y);
    void draw(graphics::IRenderer* renderer, int x, int y, const FlipFlags& f);
    void setSpeed(short speed);
    void nextFrame();

private:
    std::list<SpriteType> frames_;
    std::list<SpriteType>::iterator currentFrame_;
    BitmapsContainer& bitmapContainer_;
    short speed_;
    short currentFrameLifeTime_;
};


#endif  // ANIMATED_BITMAP_HPP_
