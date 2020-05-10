#include <SDL2/SDL.h>

class FlipFlags
{
public:
    FlipFlags();
    void no_flip();
    void flip_horizontal();
    void flip_vertical();
    SDL_RendererFlip toSDL() const;

private:
    SDL_RendererFlip flags_;
};
