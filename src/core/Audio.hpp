#ifndef CORE_AUDIO_HPP_
#define CORE_AUDIO_HPP_

#include <map>

#include <SDL2/SDL_mixer.h>

namespace core
{

enum class AudioSample
{
    BlockBreak,
    BlockHit,
    Coin,
    Explosion,
    Fireball,
    MushroomAppear,
    MushroomEat,
    PlayerJumpSmall,
    PlayerJumpBig,
    Shot,
    Stomp,
};

class Audio
{
public:
    Audio();
    ~Audio();
    void playSample(AudioSample sample);
    void playMusic();
    void stopMusic();


private:
    std::map<AudioSample, Mix_Chunk*> samples_;
    Mix_Music* music_;
};

}  // namespace core

#endif  // CORE_AUDIO_HPP_
