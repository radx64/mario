#include <SDL2/SDL.h>

class FlipFlags
{
public:
    FlipFlags();
    void NO_FLIP();
    void FLIP_HORIZONTAL();
    void FLIP_VERTICAL();
    SDL_RendererFlip getSDL() const;

private:
    SDL_RendererFlip flags_;
};
