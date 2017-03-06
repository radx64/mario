#include "character/player/GraphicsComponent.hpp"

#include "AnimatedBitmap.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include "FlipFlags.hpp"
#include "graphics/StillRenderer.hpp"
#include "Player.hpp"
#include "Sprite.hpp"

namespace character
{
namespace player
{

GraphicsComponent::GraphicsComponent(Player& player)
: player_(player)
{
    auto sprite = Context::getBitmapsContainer()->get(SpriteType::MARIO_RUNNING_0);
    player_.size.x = sprite->getWidth();
    player_.size.y = sprite->getHeight();


    runningAnimation_ = new AnimatedBitmap({
        SpriteType::MARIO_RUNNING_2,
        SpriteType::MARIO_RUNNING_0,
        SpriteType::MARIO_RUNNING_1},
        3,
        *Context::getBitmapsContainer()
    );

    standingAnimation_ = new AnimatedBitmap({SpriteType::MARIO_STANDING}, 1,
        *Context::getBitmapsContainer()
    );

    jumpAnimation_= new AnimatedBitmap({SpriteType::MARIO_JUMPING}, 1,
        *Context::getBitmapsContainer()
    );

    slideAnimation_= new AnimatedBitmap({SpriteType::MARIO_SLIDING}, 1,
        *Context::getBitmapsContainer()
    );

    currentAnimation_ = standingAnimation_;
}

void GraphicsComponent::draw()
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

    if (player_.velocity.x < 0.0)
    {
        flip.FLIP_HORIZONTAL();
    }
    else
    {
        flip.NO_FLIP();
    }

    currentAnimation_->draw(Context::getStillRenderer(),
        player_.position.x - camera->getX(),
         player_.position.y - camera->getY(), flip);
}

void GraphicsComponent::setSpeed(short speed)
{
    currentAnimation_->setSpeed(speed);
}

}  // namespace player
}  // namespace character
