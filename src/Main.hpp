#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "KeyboardState.hpp"

class SDL_Renderer;
class SDL_Window;
class Bitmap;
class TextRenderer;
class FpsCounter;

class Main
{
public:
    Main();
    ~Main();
    void init();
    void loop();
    void input();

private:
    void clear();
    void simpleScene(Bitmap& mario, Bitmap& ground, Bitmap& brick, TextRenderer& text, int& frame,
        FpsCounter& fps);
    KeyboardState keys_;
    bool running_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    const unsigned int width_;
    const unsigned int height_;
};

#endif  // MAIN_HPP_ 
