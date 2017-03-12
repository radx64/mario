#ifndef CORE_AUDIO_HPP_
#define CORE_AUDIO_HPP_

#include <map>

class Mix_Chunk;

namespace core
{

enum class AudioSample
{
    BlockBreak,
    Coin,
    MushroomAppear,
    PlayerJump,
    Stomp,
};

class Audio
{
public:
    Audio();
    ~Audio();
    void playSample(AudioSample sample);


private:
    std::map<AudioSample, Mix_Chunk*> samples_;
};

}  // namespace core

#endif  // CORE_AUDIO_HPP_
