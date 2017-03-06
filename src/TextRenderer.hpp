#ifndef TEXT_RENDERER_HPP_
#define TEXT_RENDERER_HPP_

#include <string>

#include "Sprite.hpp"

class SDL_Renderer;

class TextRenderer
{
public:
    TextRenderer();
    void draw(const std::string& text, const int& x, const int& y);
    void draw(const std::string& text, const int& x, const int& y, const float& scale);
    void setColor(int r,int g, int b);

private:
    int getOffset(const char character);
    int r_;
    int g_;
    int b_;

    Sprite font_;
    char fontCharacterBitmapWidth_;
};

#endif  //TEXT_RENDERER_HPP_
