#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

class BitmapsContainer;
class FpsCounter;
class TextRenderer;
struct KeyboardState;
class SDL_Renderer;
class World;

class Context
{
public:
    static void setBitmapsContainer(BitmapsContainer*);
    static BitmapsContainer* getBitmapsContainer();

    static void setFpsCounter(FpsCounter*);
    static FpsCounter* getFpsCounter();

    static void setTextRenderer(TextRenderer*);
    static TextRenderer* getTextRenderer();

    static void setKeyboardState(KeyboardState*);
    static KeyboardState* getKeyboardState();

    static void setRenderer(SDL_Renderer*);
    static SDL_Renderer* getRenderer();

    static void setWorld(World*);
    static World* getWorld();


private:
    static BitmapsContainer* bitmapsContainer_;
    static FpsCounter* fpsCounter_;
    static TextRenderer* textRenderer_;
    static KeyboardState* keyboardState_;
    static SDL_Renderer* renderer_;
    static World* world_;
};

#endif  // CONTEXT_HPP_
