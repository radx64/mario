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

void Context::setSdlRenderer(SDL_Renderer* r)
{
    sdlRenderer_ = r;
}
SDL_Renderer* Context::getSdlRenderer()
{
    return sdlRenderer_;
}
void Context::setStillRenderer(graphics::StillRenderer* r)
{
    stillRenderer_ = r;
}
graphics::StillRenderer* Context::getStillRenderer()
{
    return stillRenderer_;
}

void Context::setCameraRenderer(graphics::CameraRenderer* r)
{
    cameraRenderer_ = r;
}
graphics::CameraRenderer* Context::getCameraRenderer()
{
    return cameraRenderer_;
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
SDL_Renderer* Context::sdlRenderer_;
World* Context::world_;
Camera* Context::camera_;
graphics::StillRenderer* Context::stillRenderer_;
graphics::CameraRenderer* Context::cameraRenderer_;