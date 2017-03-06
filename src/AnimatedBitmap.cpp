#include "AnimatedBitmap.hpp"

#include "Sprite.hpp"

AnimatedBitmap::AnimatedBitmap(std::list<SpriteType> bitmaps,
    short speed,
    BitmapsContainer& bitmapContainer)
: frames_(bitmaps), bitmapContainer_(bitmapContainer), speed_(speed)
{
    currentFrame_ = frames_.begin();
    currentFrameLifeTime_ = 0;
}

void AnimatedBitmap::draw(graphics::IRenderer* renderer, int x, int y)
{
    bitmapContainer_.get(*currentFrame_)->draw(renderer, x, y);
}

void AnimatedBitmap::draw(graphics::IRenderer* renderer, int x, int y, const FlipFlags& f)
{
    bitmapContainer_.get(*currentFrame_)->draw(renderer, x, y, f);
}

void AnimatedBitmap::setSpeed(short speed)
{
    speed_ = speed;
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
