#include "Player.hpp"

#include "Context.hpp"
#include "KeyboardState.hpp"
#include "TextRenderer.hpp"

namespace character
{
namespace player
{

Player::Player()
: Object(ObjectType::Player),
graphics_(*this),
physics_(*this)
{
    collidable_ = true;
    moving_ = true;
}

void Player::draw(double delta_time)
{
    graphics_.draw(delta_time);
}

void Player::on_collision(Collision collision, Object& object)
{
    physics_.on_collision(collision, object);
}

void Player::on_simulate(double delta_time)
{
    physics_.simulate(delta_time);
}

void Player::on_input()
{
   auto keys = Context::getKeyboardState();
   if (keys->left) facing_left_ = true;
   if (keys->right) facing_left_ = false;

   physics_.input();
}

void Player::setAnimationDelay(double delay)
{
    graphics_.setDelay(delay);
}

std::vector<Object::CollisionPoint> Player::getCollisionPoints()
{
    if (power_level == Player::PowerLevel::Small)
        return std::vector<CollisionPoint> {
            {Collision::State::Bottom, {position.x + size.x*2.0f/6.0f,  position.y + size.y-1}},
            {Collision::State::Bottom, {position.x + size.x*4.0f/6.0f,  position.y + size.y-1}},
            {Collision::State::Top,    {position.x + size.x/2.0f,       position.y}},
            {Collision::State::Left,   {position.x ,                    position.y + size.y*1.0f/3.0f}},
            {Collision::State::Right,  {position.x + size.x,            position.y + size.y*1.0f/3.0f}},
            };
    else
        return std::vector<CollisionPoint> {
            {Collision::State::Bottom, {position.x + size.x*2.0f/6.0f,  position.y + size.y-1}},
            {Collision::State::Bottom, {position.x + size.x*4.0f/6.0f,  position.y + size.y-1}},
            {Collision::State::Top,    {position.x + size.x/2.0f,       position.y}},
            {Collision::State::Left,   {position.x ,                    position.y + size.y*1.0f/3.0f}},
            {Collision::State::Left,   {position.x ,                    position.y + size.y*2.0f/3.0f}},
            {Collision::State::Right,  {position.x + size.x,            position.y + size.y*1.0f/3.0f}},
            {Collision::State::Right,  {position.x + size.x,            position.y + size.y*2.0f/3.0f}},
            };
}

}  // namespace player
}  // namespace character
