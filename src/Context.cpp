#include "Context.hpp"

void Context::setBitmapsContainer(BitmapsContainer* bc)
{
    bitmapsContainer_ = bc;
}

BitmapsContainer* Context::getBitmapsContainer()
{
    return bitmapsContainer_;
}

void Context::setFpsCounter(FpsCounter* fc)
{
    fpsCounter_ = fc;
}

FpsCounter* Context::getFpsCounter()
{
    return fpsCounter_;
}

void Context::setTextRenderer(TextRenderer* tr)
{
    textRenderer_ = tr;
}

TextRenderer* Context::getTextRenderer()
{
    return textRenderer_;
}

void Context::setKeyboardState(KeyboardState* ks)
{
    keyboardState_ = ks;
}

KeyboardState* Context::getKeyboardState()
{
    return keyboardState_;
}

void Context::setRenderer(SDL_Renderer* r)
{
    renderer_ = r;
}
SDL_Renderer* Context::getRenderer()
{
    return renderer_;
}

void Context::setWorld(World* w)
{
    world_ = w;
}
World* Context::getWorld()
{
    return world_;
}

void Context::setCamera(Camera* c)
{
    camera_ = c;
}
Camera* Context::getCamera()
{
    return camera_;
}


BitmapsContainer* Context::bitmapsContainer_;
FpsCounter* Context::fpsCounter_;
TextRenderer* Context::textRenderer_;
KeyboardState* Context::keyboardState_;
SDL_Renderer* Context::renderer_;
World* Context::world_;
Camera* Context::camera_;
