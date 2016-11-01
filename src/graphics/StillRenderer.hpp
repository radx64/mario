#ifndef GRAPHICS_STILLRENDERER_HPP_
#define GRAPHICS_STILLRENDERER_HPP_

#include "graphics/IRenderer.hpp"

class SDL_Texture;
class SDL_Rect;
class FlipFlags;

namespace graphics
{

class StillRenderer : public IRenderer
{
public:
    virtual void draw(SDL_Texture* texture, SDL_Rect* renderQuad) override;
    virtual void draw(SDL_Texture* texture, SDL_Rect* renderQuad, const FlipFlags* flipflags)
        override;
    virtual void draw(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destination) override;
};

}  // namespace graphics


#endif  // GRAPHICS_STILLRENDERER_HPP_
