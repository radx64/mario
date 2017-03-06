#ifndef ANIMATED_SPRITE_HPP_
#define ANIMATED_SPRITE_HPP_

#include <list>
#include <string>
#include <memory>

#include "SpritesContainer.hpp"

class SDL_Renderer;
class FlipFlags;

namespace graphics
{
    class IRenderer;
}

class AnimatedSprite
{
public:
    AnimatedSprite(std::list<SpriteType> bitmaps,
        short speed,
        SpritesContainer& spritesContainer);
    void draw(graphics::IRenderer* renderer, int x, int y);
    void draw(graphics::IRenderer* renderer, int x, int y, const FlipFlags& f);
    void setSpeed(short speed);
    void nextFrame();

private:
    std::list<SpriteType> frames_;
    std::list<SpriteType>::iterator currentFrame_;
    SpritesContainer& spritesContainer_;
    short speed_;
    short currentFrameLifeTime_;
};


#endif  // ANIMATED_SPRITE_HPP_
