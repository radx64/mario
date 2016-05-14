#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

class BitmapsContainer;
class FpsCounter;
class TextRenderer;
struct KeyboardState;

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

private:
    BitmapsContainer* bitmapsContainer_;
    FpsCounter* fpsCounter_;
    TextRenderer* textRenderer_;
    KeyboardState* keyboardState_;
};

#endif  // CONTEXT_HPP_ 
