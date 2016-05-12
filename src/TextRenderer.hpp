#ifndef TEXT_RENDERER_HPP_
#define TEXT_RENDERER_HPP_

#include <string>

#include "Bitmap.hpp"

class SDL_Renderer;

class TextRenderer
{
public:
    TextRenderer(SDL_Renderer* renderer);
    void draw(const std::string text, int x, int y);
    void draw(const std::string text, int x, int y, float scale); 
    void setColor(int r,int g, int b);

private:
    int getOffset(const char character);
    int r_;
    int g_;
    int b_;

    Bitmap font_;
    SDL_Renderer* renderer_;
    char fontCharacterBitmapWidth_;
};

#endif  //TEXT_RENDERER_HPP_
