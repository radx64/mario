#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include <string>

class SDL_Renderer;
class SDL_Texture;

class Bitmap
{
public:
    Bitmap(SDL_Renderer* renderer, std::string filename);
    ~Bitmap();
    void draw(int x, int y);
    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture_;
    SDL_Renderer* renderer_;
    int width_;
    int height_;
};

#endif  // BITMAP_HPP_ 
