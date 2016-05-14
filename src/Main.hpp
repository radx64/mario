#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "KeyboardState.hpp"

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"

class SDL_Renderer;
class SDL_Window;
class Bitmap;
class TextRenderer;
class FpsCounter;
class AnimatedBitmap;

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
    void simpleScene(int& frame);
    KeyboardState keys_;
    bool running_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    const unsigned int width_;
    const unsigned int height_;
    BitmapsContainer* bitmaps_;
    AnimatedBitmap* questionBlock_;
    AnimatedBitmap* runningMario_;
    Context context_;
};

#endif  // MAIN_HPP_ 
