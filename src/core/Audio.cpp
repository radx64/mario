#include "core/Audio.hpp"

#include <iostream>

namespace core
{

Audio::Audio()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error:" << Mix_GetError() << std::endl;
        return;
    }

    samples_ = {

        { AudioSample::BlockBreak,          Mix_LoadWAV( "../audio/blockbreak.wav") },
        { AudioSample::Coin,                Mix_LoadWAV( "../audio/coin.wav") },
        { AudioSample::MushroomAppear,      Mix_LoadWAV( "../audio/mushroomappear.wav") },
        { AudioSample::PlayerJump,          Mix_LoadWAV( "../audio/jumpbig.wav") },
        { AudioSample::Stomp,               Mix_LoadWAV( "../audio/stomp.wav") },

    };

    music_ = Mix_LoadMUS( "../audio/overworld.wav" );
}


void Audio::playMusic()
{
    Mix_PlayMusic(music_, -1);
}

void Audio::stopMusic()
{
    Mix_HaltMusic();
}

Audio::~Audio()
{
    for (auto& samplePair : samples_)
    {
        Mix_FreeChunk(samplePair.second);
    }

    Mix_FreeMusic(music_);
    Mix_Quit();
}

void Audio::playSample(AudioSample sample)
{
    try
    {
        Mix_PlayChannel( static_cast<int>(sample),  //one channel per effect ? hmm...
            samples_.at(sample), 0 ); // channel -1 will give any random avaialbe channel
    }

    catch (std::out_of_range e)
    {
        std::cout << "Requested sprite is not in container" << std::endl;
    }

}






}  // namespace core