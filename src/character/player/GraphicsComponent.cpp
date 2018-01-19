#include "character/player/GraphicsComponent.hpp"

#include "AnimatedSprite.hpp"
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
    auto sprite = Context::getSpritesContainer()->get(SpriteType::MARIO_RUNNING_0);
    player_.size.x = sprite->getWidth();
    player_.size.y = sprite->getHeight();

    runningAnimation_ = new AnimatedSprite({
        SpriteType::MARIO_RUNNING_2,
        SpriteType::MARIO_RUNNING_0,
        SpriteType::MARIO_RUNNING_1},
        3,
        *Context::getSpritesContainer());

    standingAnimation_ = new AnimatedSprite({SpriteType::MARIO_STANDING}, 1,
        *Context::getSpritesContainer());

    jumpAnimation_= new AnimatedSprite({SpriteType::MARIO_JUMPING}, 1,
        *Context::getSpritesContainer());

    slideAnimation_= new AnimatedSprite({SpriteType::MARIO_SLIDING}, 1,
        *Context::getSpritesContainer());

    crouchAnimation_ = new AnimatedSprite({SpriteType::MARIO_CROUCHING}, 1,
        *Context::getSpritesContainer());

    currentAnimation_ = standingAnimation_;
}

//TODO: This whole draw method logic shold be moved outside. Draw need to draw, not calculate different things.

void GraphicsComponent::draw()
{
   currentAnimation_->nextFrame();

   switch (player_.state)
   {
        case Player::State::Standing : currentAnimation_ = standingAnimation_;  break;
        case Player::State::Running : currentAnimation_  = runningAnimation_;   break;
        case Player::State::Jumping : currentAnimation_  = jumpAnimation_;      break;
        case Player::State::Sliding : currentAnimation_ = slideAnimation_;      break;
        case Player::State::Crouching : currentAnimation_ = crouchAnimation_;   break;
   }

    if (player_.state != player_.previousState)
    {
        auto spriteSize = currentAnimation_->getSize();
        math::Vector2f size = {static_cast<float>(spriteSize.x), static_cast<float>(spriteSize.y)};
        player_.size = size;


        if (player_.state == Player::State::Crouching)
        {
            player_.position.y += 10;
        }

        if (player_.previousState == Player::State::Crouching )
        {
            player_.position.y -= 10;
        }
    }    

    player_.previousState = player_.state; 

    auto camera = Context::getCamera();

    if (fabs(player_.velocity.x) > 5.0 ) 
        player_.state = Player::State::Running;
    else
        player_.state = Player::State::Standing;

    if (player_.jumped_) player_.state = Player::State::Jumping;
    if (player_.crouched_ ) player_.state = Player::State::Crouching;

    FlipFlags flip;

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

void GraphicsComponent::setDelay(short delay)
{
    currentAnimation_->setDelay(delay);
}

}  // namespace player
}  // namespace character
