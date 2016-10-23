#include "PlayerGraphicsComponent.hpp"

#include <SDL2/SDL.h>

#include "AnimatedBitmap.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "FlipFlags.hpp"
#include "Player.hpp"

namespace character
{

PlayerGraphicsComponent::PlayerGraphicsComponent(Player& player)
: player_(player)
{
    runningAnimation_ = new AnimatedBitmap({
        BitmapType::MARIO_RUNNING_2,
        BitmapType::MARIO_RUNNING_0,
        BitmapType::MARIO_RUNNING_1},
        5,
        *Context::getBitmapsContainer()
    );

    standingAnimation_ = new AnimatedBitmap({BitmapType::MARIO_STANDING}, 1,
        *Context::getBitmapsContainer()
    );

    jumpAnimation_= new AnimatedBitmap({BitmapType::MARIO_JUMPING}, 1,
        *Context::getBitmapsContainer()
    );

    slideAnimation_= new AnimatedBitmap({BitmapType::MARIO_SLIDING}, 1,
        *Context::getBitmapsContainer()
    );

    currentAnimation_ = standingAnimation_;
}

PlayerGraphicsComponent::~PlayerGraphicsComponent(){}

void PlayerGraphicsComponent::draw()
{
   currentAnimation_->nextFrame();

   switch (player_.state)
   {
        case Player::State::Standing : currentAnimation_ = standingAnimation_; break;
        case Player::State::Running : currentAnimation_  = runningAnimation_; break;
        case Player::State::Jumping : currentAnimation_  = jumpAnimation_; break;
        case Player::State::Sliding : currentAnimation_ = slideAnimation_; break;
   }
    FlipFlags flip;

    auto camera = Context::getCamera();

    if (player_.ax < 0.2)
    {
        flip.FLIP_HORIZONTAL();
    }
    else
    {
        flip.NO_FLIP();
    }

    currentAnimation_->draw(player_.x - camera->getX(), player_.y - camera->getY(), flip);

    /* some debug draws below */

    // auto renderer = Context::getRenderer();


    // SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x77);
    // SDL_RenderDrawLine(renderer,
    //     (int)player_.x, (int)player_.y, (int)player_.x+(int)player_.ax*4.0, (int)player_.y);

    // SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x77);
    // SDL_RenderDrawLine(
    //     renderer, (int)player_.x, (int)player_.y, (int)player_.x, (int)player_.y+(int)player_.ay*4.0);

    // if (fabs(player_.ax) > 1.0 || fabs(player_.ay) > 1.0)
    // {
    //     debugFrames_.push_back({player_.x,player_.y});
    // }

    // if (debugFrames_.size() > 30)
    // {
    //     debugFrames_.erase(debugFrames_.begin());
    // }

    // for (auto frame : debugFrames_)
    // {
    //     SDL_Rect r{(int)frame.first, (int)frame.second, (int)player_.w, (int)player_.h};
    //     SDL_RenderDrawRect(renderer, &r);
    // }

    // SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xAA, 0x77);
    // SDL_Rect r{(int)player_.x, (int)player_.y, (int)player_.w, (int)player_.h};
    // SDL_RenderDrawRect(renderer, &r);
}

}  // namespace character
