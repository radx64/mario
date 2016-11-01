#include "graphics/CameraRenderer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "FlipFlags.hpp"
#include <SDL2/SDL.h>

namespace graphics
{

CameraRenderer::CameraRenderer(Camera* cameraToFollow) : camera_(cameraToFollow)
{}

bool isRenderNeeded(SDL_Rect* coords, Camera* camera)
{
    if (coords->x + coords->w < 0) return false;
    if (coords->y + coords->h < 0) return false;

    if (coords->x - coords->w > camera->getW()) return false;
    if (coords->y - coords->h > camera->getH()) return false; 
    return true;    
}

void CameraRenderer::draw(SDL_Texture* texture, SDL_Rect* renderQuad)
{
    renderQuad->x -= camera_->getX();
    renderQuad->y -= camera_->getY();

    if (isRenderNeeded(renderQuad, camera_))
    {
        SDL_RenderCopy(Context::getSdlRenderer(), texture, nullptr, renderQuad);
    }
}

void CameraRenderer::draw(SDL_Texture* texture, SDL_Rect* renderQuad, const FlipFlags* flipflags)
{
    renderQuad->x -= camera_->getX();
    renderQuad->y -= camera_->getY();

    if (isRenderNeeded(renderQuad, camera_))
    {
        SDL_RenderCopyEx(Context::getSdlRenderer(),
            texture,
            NULL,
            renderQuad,
            0,
            NULL,
            flipflags->getSDL());
    }
}

void CameraRenderer::draw(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destination)
{
    destination->x -= camera_->getX();
    destination->y -= camera_->getY();
    if (isRenderNeeded(destination, camera_))
    {
        SDL_RenderCopy(Context::getSdlRenderer(), texture, source, destination);
    }
}

}  // namespace graphics

