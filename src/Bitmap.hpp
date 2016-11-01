#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include <string>

class SDL_Texture;
class SDL_Rect;
class FlipFlags;

namespace graphics
{
    class IRenderer;
}

class Bitmap
{
public:
    Bitmap(const std::string& filename);
    ~Bitmap();
    void draw(graphics::IRenderer* renderer, int x, int y);
    void draw(graphics::IRenderer* renderer, int x, int y, const FlipFlags& flip);
    void copy(graphics::IRenderer* renderer, SDL_Rect* source, SDL_Rect* destination);
    void setColor(int r, int g, int b);
    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture_;
    std::string filename_;
    int width_;
    int height_;
};

#endif  // BITMAP_HPP_
