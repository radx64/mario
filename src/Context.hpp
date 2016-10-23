#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

class BitmapsContainer;
class FpsCounter;
class TextRenderer;
struct KeyboardState;
class SDL_Renderer;
class World;
class Camera;

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

    static void setCamera(Camera*);
    static Camera* getCamera();


private:
    static BitmapsContainer* bitmapsContainer_;
    static FpsCounter* fpsCounter_;
    static TextRenderer* textRenderer_;
    static KeyboardState* keyboardState_;
    static SDL_Renderer* renderer_;
    static World* world_;
    static Camera* camera_;
};

#endif  // CONTEXT_HPP_
