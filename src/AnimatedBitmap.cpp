#include "AnimatedBitmap.hpp"

AnimatedBitmap::AnimatedBitmap(std::list<BitmapType> bitmaps, 
    short speed, 
    BitmapsContainer& bitmapContainer)
: frames_(bitmaps), bitmapContainer_(bitmapContainer), speed_(speed)
{
    currentFrame_ = frames_.begin();
    currentFrameLifeTime_ = 0;
}

void AnimatedBitmap::draw(int x, int y)
{
    bitmapContainer_.get(*currentFrame_)->draw(x,y);
}

void AnimatedBitmap::nextFrame()
{
    currentFrameLifeTime_++;
    if (currentFrameLifeTime_ > speed_)
    {
        ++currentFrame_;
        currentFrameLifeTime_ = 0;
        if (currentFrame_ == frames_.end())
        {
            currentFrame_ = frames_.begin();
        }
    }    
}
