#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

class  BitmapsContainer;
class  FpsCounter;
class  TextRenderer;
struct KeyboardState;
class  SDL_Renderer;

class Context
{
public:
    void setBitmapsContainer(BitmapsContainer*);
    BitmapsContainer* getBitmapsContainer();

    void setFpsCounter(FpsCounter*);
    FpsCounter* getFpsCounter();

    void setTextRenderer(TextRenderer*);
    TextRenderer* getTextRenderer();

    void setKeyboardState(KeyboardState*);
    KeyboardState* getKeyboardState();

    void setRenderer(SDL_Renderer*);
    SDL_Renderer* getRenderer();

private:
    BitmapsContainer* bitmapsContainer_;
    FpsCounter* fpsCounter_;
    TextRenderer* textRenderer_;
    KeyboardState* keyboardState_;
    SDL_Renderer* renderer_;
};

#endif  // CONTEXT_HPP_ 
