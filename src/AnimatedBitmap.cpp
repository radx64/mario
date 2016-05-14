#include "AnimatedBitmap.hpp"

AnimatedBitmap::AnimatedBitmap(SDL_Renderer* renderer, std::list<std::string> files, short speed)
: speed_(speed)
{
    for (const auto& file : files)
    {
        std::shared_ptr<Bitmap> frame = std::make_shared<Bitmap>(renderer, file);
        frames_.emplace_back(frame);
    } 
    currentFrame_ = frames_.begin();
    currentFrameLifeTime_ = 0;
}

void AnimatedBitmap::setColor(int r, int g, int b)
{
    for (auto frame : frames_)
    {
        frame->setColor(r, g, b);
    }
}

void AnimatedBitmap::draw(int x, int y)
{

    (*currentFrame_)->draw(x,y);
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
