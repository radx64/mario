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
