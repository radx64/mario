#ifndef ANIMATED_BITMAP_HPP_
#define ANIMATED_BITMAP_HPP_

#include <list>
#include <string>
#include <memory>

#include "Bitmap.hpp"

class SDL_Renderer;

class AnimatedBitmap
{
public:
    AnimatedBitmap(SDL_Renderer* renderer, std::list<std::string> files, short speed);
    void draw(int x, int y);
    void setColor(int r, int g, int b);

private:
    std::list<std::shared_ptr<Bitmap>> frames_;
    std::list<std::shared_ptr<Bitmap>>::iterator currentFrame_;
    short speed_;
    short currentFrameLifeTime_;
};


#endif  // ANIMATED_BITMAP_HPP_
