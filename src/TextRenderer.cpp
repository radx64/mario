#include "TextRenderer.hpp"

#include <SDL2/SDL.h>

TextRenderer::TextRenderer(SDL_Renderer* renderer) 
: font_(renderer, "../img/font.bmp"), renderer_(renderer), fontCharacterBitmapWidth_(8)
{
    r_ = 0xFF;
    g_ = 0xFF;
    b_ = 0xFF;
}

void TextRenderer::draw(const std::string& text, int x, int y)
{
    font_.setColor(r_, g_, b_);
    SDL_Rect crop;
    SDL_Rect render;

    crop.w = fontCharacterBitmapWidth_;
    crop.h = fontCharacterBitmapWidth_;

    render.y = y;
    render.w = fontCharacterBitmapWidth_;
    render.h = fontCharacterBitmapWidth_;

    for (unsigned int index = 0; index < text.size(); ++index)
    {
        crop.x = getOffset(text.at(index));
        render.x = x + fontCharacterBitmapWidth_ * index;
        font_.copy(&crop, &render);
    }
}

int TextRenderer::getOffset(const char character)
{
    if (character >= '+' && character < '[')
    {
        return (character - '*') * fontCharacterBitmapWidth_;
    }
    else if (character >= 'a' && character < 'z')
    {
        return (character - 'J') * fontCharacterBitmapWidth_;
    }
    else return 0;
}

void TextRenderer::setColor(int r,int g, int b)
{
    r_ = r;
    g_ = g;
    b_ = b;
}
