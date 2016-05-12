#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "KeyboardState.hpp"

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
    KeyboardState keys_;
    bool running_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    const unsigned int width_;
    const unsigned int height_;
};

#endif  // MAIN_HPP_ 
