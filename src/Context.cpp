#include "Context.hpp"

void Context::setAudio(core::Audio* a)
{
    audio_ = a;
}

core::Audio* Context::getAudio()
{
    return audio_;
}

void Context::setSpritesContainer(SpritesContainer* sc)
{
    spritesContainer_ = sc;
}

SpritesContainer* Context::getSpritesContainer()
{
    return spritesContainer_;
}

void Context::setFpsCounter(core::FpsCounter* fc)
{
    fpsCounter_ = fc;
}

core::FpsCounter* Context::getFpsCounter()
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


Camera* Context::camera_;
core::Audio* Context::audio_;
core::FpsCounter* Context::fpsCounter_;
graphics::CameraRenderer* Context::cameraRenderer_;
graphics::StillRenderer* Context::stillRenderer_;
KeyboardState* Context::keyboardState_;
SDL_Renderer* Context::sdlRenderer_;
SpritesContainer* Context::spritesContainer_;
TextRenderer* Context::textRenderer_;
World* Context::world_;