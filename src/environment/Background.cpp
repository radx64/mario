#include "Background.hpp"

#include "SpritesContainer.hpp"
#include "Context.hpp"
#include "graphics/CameraRenderer.hpp"

namespace environment
{

Background::Background(SpriteType sprite) : Object(ObjectType::Background)
{
    sprite_ = Context::getSpritesContainer()->get(sprite);
    size.y = sprite_->getHeight();
    size.x = sprite_->getWidth();
}

void Background::draw()
{
    sprite_->draw(Context::getCameraRenderer(), position.x, position.y);
}

void Background::onUpdate(std::vector<Object*> gameObjects)
{
    (void) gameObjects;
}

void Background::onCollisionWith(Collision collision, Object& object)
{
    (void) collision;
    (void) object;
}

}  // namespace environment
