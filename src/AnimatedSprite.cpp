#include "AnimatedSprite.hpp"

#include "Sprite.hpp"

AnimatedSprite::AnimatedSprite(std::list<SpriteType> bitmaps,
    double delay,
    SpritesContainer& spritesContainer)
: frames_(bitmaps), spritesContainer_(spritesContainer), delay_(delay)
{
    currentFrame_ = frames_.begin();
    currentFrameLifeTime_ = 0;
}

void AnimatedSprite::draw(graphics::IRenderer* renderer, int x, int y)
{
    spritesContainer_.get(*currentFrame_)->draw(renderer, x, y);
}

void AnimatedSprite::draw(graphics::IRenderer* renderer, int x, int y, const FlipFlags& f)
{
    spritesContainer_.get(*currentFrame_)->draw(renderer, x, y, f);
}

void AnimatedSprite::setDelay(double delay)
{
    delay_ = delay;
}

void AnimatedSprite::nextFrame(double delta_time)
{
    currentFrameLifeTime_+= delta_time;
    if (currentFrameLifeTime_ > delay_)
    {
        ++currentFrame_;
        currentFrameLifeTime_ = 0.0;
        if (currentFrame_ == frames_.end())
        {
            currentFrame_ = frames_.begin();
        }
    }
}

math::Vector2i AnimatedSprite::getSize()
{
    return spritesContainer_.get(*currentFrame_)->getSize();
}
