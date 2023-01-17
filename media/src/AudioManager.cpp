#include "sgl/media/AudioManager.h"

#include "sgl/media/Music.h"
#include "sgl/media/Sound.h"

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

// -- SFX --
Sound * AudioManager::CreateSound(const char * filename)
{
    std::string strFile(filename);

    auto it = mSounds.find(strFile);

    if(it != mSounds.end())
        return it->second;

    auto sound = new Sound(filename);

    if(sound->IsValid())
    {
        mSounds.emplace(strFile, sound);
        return sound;
    }
    else
    {
        delete sound;
        return nullptr;
    }
}

Sound * AudioManager::GetSound(const char * filename)
{
    std::string strFile(filename);

    auto it = mSounds.find(strFile);

    if(it != mSounds.end())
        return it->second;
    else
        return nullptr;
}

// -- MUSIC --
Music * AudioManager::CreateMusic(const char * filename)
{
    std::string strFile(filename);

    auto it = mMusic.find(strFile);

    if(it != mMusic.end())
        return it->second;

    auto music = new Music(filename);

    if(music->IsValid())
    {
        mMusic.emplace(strFile, music);
        return music;
    }
    else
    {
        delete music;
        return nullptr;
    }
}

Music * AudioManager::GetMusic(const char * filename)
{
    std::string strFile(filename);

    auto it = mMusic.find(strFile);

    if(it != mMusic.end())
        return it->second;
    else
        return nullptr;
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
    // delete all music
    for(const auto & it : mMusic)
        delete it.second;

    // delete all sounds
    for(const auto & it : mSounds)
        delete it.second;

    // close audio device
    Mix_CloseAudio();

    // shut down
    Mix_Quit();
}

} // namespace media
} // namespace sgl
