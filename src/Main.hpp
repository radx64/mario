#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <vector>

#include "AnimatedBitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include "KeyboardState.hpp"
#include "Object.hpp"
#include "World.hpp"

class AnimatedBitmap;
class Bitmap;
class FpsCounter;
class TextRenderer;

class SDL_Renderer;
class SDL_Window;

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
    void simpleScene();
    void initGameObjects();
    void initBitmapsContainter();
    KeyboardState keys_;
    bool running_{true};
    int frame_{};
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    const unsigned int width_;
    const unsigned int height_;
    BitmapsContainer* bitmaps_;
    AnimatedBitmap* questionBlock_;
    Context context_;
    std::vector<Object*> gameObjects_;
    World world_;
    Object* player_;
    float desiredFPS_{60.0};
};

#endif  // MAIN_HPP_
