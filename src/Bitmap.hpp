#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include <string>

class SDL_Renderer;
class SDL_Texture;
class SDL_Rect;

class Bitmap
{
public:
    Bitmap(SDL_Renderer* renderer, const std::string& filename);
    ~Bitmap();
    void draw(int x, int y);
    void copy(SDL_Rect* source, SDL_Rect* destination);
    void setColor(int r, int g, int b);
    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture_;
    SDL_Renderer* renderer_;
    std::string filename_;
    int width_;
    int height_;
};

#endif  // BITMAP_HPP_ 
