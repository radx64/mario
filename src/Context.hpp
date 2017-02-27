#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

class BitmapsContainer;

namespace core
{
    class FpsCounter;
} // namespace core

class TextRenderer;
struct KeyboardState;
class SDL_Renderer;
class World;
class Camera;

namespace graphics
{
    class StillRenderer;
    class CameraRenderer;
}  // namespace graphics

class Context
{
public:
    static void setBitmapsContainer(BitmapsContainer*);
    static BitmapsContainer* getBitmapsContainer();

    static void setFpsCounter(core::FpsCounter*);
    static core::FpsCounter* getFpsCounter();

    static void setTextRenderer(TextRenderer*);
    static TextRenderer* getTextRenderer();

    static void setKeyboardState(KeyboardState*);
    static KeyboardState* getKeyboardState();

    static void setSdlRenderer(SDL_Renderer*);
    static SDL_Renderer* getSdlRenderer();

    static void setStillRenderer(graphics::StillRenderer*);
    static graphics::StillRenderer* getStillRenderer();

    static void setCameraRenderer(graphics::CameraRenderer*);
    static graphics::CameraRenderer* getCameraRenderer();

    static void setWorld(World*);
    static World* getWorld();

    static void setCamera(Camera*);
    static Camera* getCamera();


private:
    static BitmapsContainer* bitmapsContainer_;
    static core::FpsCounter* fpsCounter_;
    static TextRenderer* textRenderer_;
    static KeyboardState* keyboardState_;
    static SDL_Renderer* sdlRenderer_;
    static World* world_;
    static Camera* camera_;
    static graphics::StillRenderer* stillRenderer_;
    static graphics::CameraRenderer* cameraRenderer_;
};

#endif  // CONTEXT_HPP_
