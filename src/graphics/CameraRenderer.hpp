#ifndef GRAPHICS_CAMERARENDERER_HPP_
#define GRAPHICS_CAMERARENDERER_HPP_

#include "graphics/IRenderer.hpp"

class SDL_Texture;
class SDL_Rect;
class FlipFlags;
class Camera;

namespace graphics
{

class CameraRenderer : public IRenderer
{
public:
    CameraRenderer(Camera* cameraToFollow);

    virtual void draw(SDL_Texture* texture, SDL_Rect* renderQuad) override;
    virtual void draw(SDL_Texture* texture, SDL_Rect* renderQuad, const FlipFlags* flipflags)
        override;
    virtual void draw(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destination) override;
protected:
    Camera* camera_;
};

}  // namespace graphics


#endif  // GRAPHICS_CAMERARENDERER_HPP_
