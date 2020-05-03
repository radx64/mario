#include "Background.hpp"

#include "SpritesContainer.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"

namespace environment
{

Background::Background(SpriteType sprite) : Object(ObjectType::Background)
{
    sprite_ = Context::getSprites()->get(sprite);
    size.y = sprite_->getHeight();
    size.x = sprite_->getWidth();
}

void Background::draw(double delta_time)
{
    (void) delta_time;
    sprite_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Background::on_simulate(double timeStep)
{
    (void) timeStep;
}

void Background::on_collision(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
