#include "graphics/CameraRenderer.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "FlipFlags.hpp"
#include <SDL2/SDL.h>

namespace graphics
{

CameraRenderer::CameraRenderer(Camera* cameraToFollow) : camera_(cameraToFollow)
{

}

void CameraRenderer::draw(SDL_Texture* texture, SDL_Rect* renderQuad)
{
    renderQuad->x -= camera_->getX();
    renderQuad->y -= camera_->getY();

    if (renderQuad->x + renderQuad->w < 0) return;
    if (renderQuad->y + renderQuad->h < 0) return;

    if (renderQuad->x - renderQuad->w > camera_->getW()) return;
    if (renderQuad->y - renderQuad->h > camera_->getH()) return;  

    SDL_RenderCopy(Context::getSdlRenderer(), texture, nullptr, renderQuad);
}

void CameraRenderer::draw(SDL_Texture* texture, SDL_Rect* renderQuad, const FlipFlags* flipflags)
{
    renderQuad->x -= camera_->getX();
    renderQuad->y -= camera_->getY();

    if (renderQuad->x + renderQuad->w < 0) return;
    if (renderQuad->y + renderQuad->h < 0) return;

    if (renderQuad->x - renderQuad->w > camera_->getW()) return;
    if (renderQuad->y - renderQuad->h > camera_->getH()) return; 
    // TODO: get rid of above code duplication
    SDL_RenderCopyEx(Context::getSdlRenderer(),
        texture,
        NULL,
        renderQuad,
        0,
        NULL,
        flipflags->getSDL());
}

void CameraRenderer::draw(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destination)
{
    destination->x -= camera_->getX();
    destination->y -= camera_->getY();

    if (destination->x + destination->w < 0) return;
    if (destination->y + destination->h < 0) return;

    if (destination->x - destination->w > camera_->getW()) return;
    if (destination->y - destination->h > camera_->getH()) return; 
    SDL_RenderCopy(Context::getSdlRenderer(), texture, source, destination);
}

}  // namespace graphics

