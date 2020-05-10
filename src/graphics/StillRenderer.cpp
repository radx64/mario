#include "graphics/StillRenderer.hpp"
#include "Context.hpp"
#include "FlipFlags.hpp"
#include <SDL2/SDL.h>

namespace graphics
{

void StillRenderer::draw(SDL_Texture* texture, SDL_Rect* renderQuad)
{

    SDL_RenderCopy(Context::getSdlRenderer(), texture, nullptr, renderQuad);
}

void StillRenderer::draw(SDL_Texture* texture, SDL_Rect* renderQuad, const FlipFlags* flipflags)
{
    SDL_RenderCopyEx(Context::getSdlRenderer(),
        texture,
        NULL,
        renderQuad,
        0,
        NULL,
        flipflags->toSDL());
}

void StillRenderer::draw(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destination)
{
    SDL_RenderCopy(Context::getSdlRenderer(), texture, source, destination);
}

}  // namespace graphics

