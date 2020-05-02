#ifndef ANIMATED_SPRITE_HPP_
#define ANIMATED_SPRITE_HPP_

#include <list>
#include <string>
#include <memory>

#include "math/Vector2.hpp"
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
        double speed,
        SpritesContainer& spritesContainer);
    void draw(graphics::IRenderer* renderer, int x, int y);
    void draw(graphics::IRenderer* renderer, int x, int y, const FlipFlags& f);
    void setDelay(double delay);
    void nextFrame(double delta_time);
    math::Vector2i getSize(); 

private:
    std::list<SpriteType> frames_;
    std::list<SpriteType>::iterator currentFrame_;
    SpritesContainer& spritesContainer_;
    double delay_;
    double currentFrameLifeTime_;
};


#endif  // ANIMATED_SPRITE_HPP_
