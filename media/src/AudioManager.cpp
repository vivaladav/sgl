#include "sgl/media/AudioManager.h"

#ifdef LINUX
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
#else
    #include <SDL.h>
    #include <SDL_mixer.h>
#endif

#include <iostream>

namespace sgl
{
namespace media
{

AudioManager * AudioManager::mInstance = nullptr;

AudioManager * AudioManager::Create()
{
    if(!mInstance)
        mInstance = new AudioManager;

    return mInstance;
}

void AudioManager::Destroy()
{
    delete mInstance;
    mInstance = nullptr;
}

bool AudioManager::PlaySound(const char * filename)
{
    Mix_Chunk * chunk = Mix_LoadWAV(filename);

    if(nullptr == chunk)
    {
        std::cout << "AudioManager::PlaySound ERROR: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "AudioManager::PlaySound master volume: " << Mix_MasterVolume(-1) << std::endl;
    std::cout << "AudioManager::PlaySound channels volume: " << Mix_Volume(-1, -1) << std::endl;
    std::cout << "AudioManager::PlaySound chunk volume: " << Mix_VolumeChunk(chunk, -1) << std::endl;

    if(Mix_PlayChannel(-1, chunk, 0) == -1)
        std::cout << "AudioManager::PlaySound ERROR: " << SDL_GetError() << std::endl;

    // can't be called until chunk is played
    //Mix_FreeChunk(chunk);

    std::cout << "AudioManager::PlaySound OK" << std::endl;

    return true;
}

bool AudioManager::PlayMusic(const char * filename)
{
    Mix_Music * music = Mix_LoadMUS(filename);

    if(nullptr == music)
    {
        std::cout << "AudioManager::PlayMusic ERROR: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "AudioManager::PlayMusic master volume: " << Mix_MasterVolume(-1) << std::endl;
    std::cout << "AudioManager::PlayMusic channels volume: " << Mix_Volume(-1, -1) << std::endl;
    std::cout << "AudioManager::PlayMusic music channel volume: " << Mix_VolumeMusic(-1) << std::endl;
    std::cout << "AudioManager::PlayMusic music volume: " << Mix_GetMusicVolume(music) << std::endl;
    std::cout << "AudioManager::PlayMusic music duration: " << Mix_MusicDuration(music) << std::endl;

    if(Mix_PlayMusic(music, 0) == -1)
        std::cout << "AudioManager::PlayMusic ERROR: " << SDL_GetError() << std::endl;

    std::cout << "AudioManager::PlayMusic OK" << std::endl;

    return true;
}

void AudioManager::StopMusic()
{
    Mix_HaltMusic();
}

void AudioManager::FadeOutMusic(int ms)
{
    Mix_FadeOutMusic(ms);
}

AudioManager::AudioManager()
{
    const int frequency = 48000;
    const unsigned short format = AUDIO_S32SYS;
    const int channels = 2;
    const int bufferSize = 2048;

    if(Mix_OpenAudio(frequency, format, channels, bufferSize) == -1)
    {
        std::cout << "AudioManager ERROR: " << SDL_GetError() << std::endl;
        mValid = false;
    }

    int currFrequency = 0;
    unsigned short currFormat = 0;
    int currChannels = 0;

    Mix_QuerySpec(&currFrequency, &currFormat, &currChannels);

    std::cout << "AudioManager OK - freq: " << currFrequency << "/" << frequency
              << " - form: " << currFormat << "/" << format
              << " - chan: " << currChannels << "/" << channels << std::endl;

    mValid = true;
}

AudioManager::~AudioManager()
{
    Mix_CloseAudio();
    Mix_Quit();
}

} // namespace media
} // namespace sgl
