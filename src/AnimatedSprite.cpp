#include "AnimatedSprite.hpp"

#include "Sprite.hpp"

AnimatedSprite::AnimatedSprite(std::list<SpriteType> bitmaps,
    short speed,
    SpritesContainer& spritesContainer)
: frames_(bitmaps), spritesContainer_(spritesContainer), speed_(speed)
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

void AnimatedSprite::setSpeed(short speed)
{
    speed_ = speed;
}

void AnimatedSprite::nextFrame()
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
