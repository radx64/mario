#include "character/player/Graphics.hpp"

#include <cmath>

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

Graphics::Graphics(Player& player)
: player_(player)
{
    auto sprite = Context::getSprites()->get(SpriteType::MARIO_SMALL_STANDING);
    player_.size.x = sprite->getWidth();
    player_.size.y = sprite->getHeight();

    animations_ =
    {
            {Animation::Big_Running, new AnimatedSprite({SpriteType::MARIO_BIG_RUNNING_2,
                                                        SpriteType::MARIO_BIG_RUNNING_0,
                                                        SpriteType::MARIO_BIG_RUNNING_1},
                                                        0.0,
                                                        *Context::getSprites())},

            {Animation::Big_Standing, new AnimatedSprite({SpriteType::MARIO_BIG_STANDING}, 1,
                                                         *Context::getSprites())},

            {Animation::Big_Jumping, new AnimatedSprite({SpriteType::MARIO_BIG_JUMPING}, 1,
                                                        *Context::getSprites())},

            {Animation::Big_Sliding, new AnimatedSprite({SpriteType::MARIO_BIG_SLIDING}, 1,
                                                        *Context::getSprites())},

            {Animation::Big_Crouching, new AnimatedSprite({SpriteType::MARIO_BIG_CROUCHING}, 1,
                                                          *Context::getSprites())},

            {Animation::Small_Running, new AnimatedSprite({SpriteType::MARIO_SMALL_RUNNING_2,
                                                         SpriteType::MARIO_SMALL_RUNNING_0,
                                                         SpriteType::MARIO_SMALL_RUNNING_1},
                                                        0.0,
                                                        *Context::getSprites())},

            {Animation::Small_Standing, new AnimatedSprite({SpriteType::MARIO_SMALL_STANDING}, 1,
                                                         *Context::getSprites())},

            {Animation::Small_Jumping, new AnimatedSprite({SpriteType::MARIO_SMALL_JUMPING}, 1,
                                                        *Context::getSprites())},

            {Animation::Small_Sliding, new AnimatedSprite({SpriteType::MARIO_SMALL_SLIDING}, 1,
                                                        *Context::getSprites())},




    };

    currentAnimation_ = animations_[Animation::Big_Standing];
}

void Graphics::draw(double delta_time)
{
   currentAnimation_->nextFrame(delta_time);

   if (player_.power_level == Player::PowerLevel::Small)
   {
       switch (player_.state)
       {
            case Player::State::Standing : currentAnimation_ = animations_[Animation::Small_Standing];       break;
            case Player::State::Running : currentAnimation_  = animations_[Animation::Small_Running];        break;
            case Player::State::Jumping : currentAnimation_  = animations_[Animation::Small_Jumping];        break;
            case Player::State::Sliding : currentAnimation_  = animations_[Animation::Small_Sliding];        break;
            case Player::State::Crouching : break;
       }
   }
   else if(player_.power_level == Player::PowerLevel::Big)
   {
       switch (player_.state)
       {
           case Player::State::Standing : currentAnimation_ = animations_[Animation::Big_Standing];          break;
           case Player::State::Running : currentAnimation_  = animations_[Animation::Big_Running];           break;
           case Player::State::Jumping : currentAnimation_  = animations_[Animation::Big_Jumping];           break;
           case Player::State::Sliding : currentAnimation_  = animations_[Animation::Big_Sliding];           break;
           case Player::State::Crouching : currentAnimation_ = animations_[Animation::Big_Crouching];        break;
       }
   }

    if (player_.state != player_.previousState || player_.previous_power_level != player_.power_level) //to not swap sprites every update
    {
        auto spriteSize = currentAnimation_->getSize();
        math::Vector2f size = {static_cast<float>(spriteSize.x), static_cast<float>(spriteSize.y)};
        player_.size = size;

        if (player_.power_level != Player::PowerLevel::Small)
        {
            if (player_.state == Player::State::Crouching)
            {
                    player_.position.y += 10;
            }

            if (player_.previousState == Player::State::Crouching)
            {
                player_.position.y -= 10;
            }
        }
    }    

    player_.previousState = player_.state; 

    auto camera = Context::getCamera();

    FlipFlags flip;

    if (player_.facing_left_)
        flip.flip_horizontal();
    else
        flip.no_flip();

    currentAnimation_->draw(Context::getStillRenderer(),
        player_.position.x - camera->getX(),
         player_.position.y - camera->getY(), flip);
}

void Graphics::setDelay(double delay)
{
    if (player_.power_level == Player::PowerLevel::Small)
        currentAnimation_->setDelay(delay / 2.0);
    else
        currentAnimation_->setDelay(delay);

}

}  // namespace player
}  // namespace character
