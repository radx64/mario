#ifndef GRAPHICS_IRENDERER_HPP_
#define GRAPHICS_IRENDERER_HPP_

class SDL_Texture;
class SDL_Rect;
class FlipFlags;

namespace graphics
{

class IRenderer
{
public:
    virtual void draw(SDL_Texture* texture, SDL_Rect* renderQuad) = 0;
    virtual void draw(SDL_Texture* texture, SDL_Rect* renderQuad, const FlipFlags* flipflags) = 0;
    virtual void draw(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destination) = 0;
};

}  // namespace graphics


#endif  // GRAPHICS_IRENDERER_HPP_
