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
    void draw(SDL_Renderer* renderer, int x, int y);

private:
    SDL_Texture* texture_;
    int width_;
    int height_;
};

#endif  // BITMAP_HPP_ 
