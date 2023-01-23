#include "sgl/media/AudioManager.h"

#include "sgl/media/AudioPlayer.h"
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
#include <cmath>

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

void AudioManager::Update(float delta)
{
    mPlayer->Update(delta);
}

// -- SFX --
Sound * AudioManager::CreateSound(const char * filename)
{
    // check if sound is already available
    const std::string strFile(filename);
    const std::size_t fileId = GetFileId(strFile);

    Sound * sound = GetSound(fileId);

    if(sound != nullptr)
        return sound;

    // sound not found -> create it
    sound = new Sound(filename);

    if(sound->IsValid())
    {
        mSounds.emplace(fileId, sound);
        return sound;
    }
    else
    {
        delete sound;
        return nullptr;
    }
}

Sound * AudioManager::CreateSound(const core::DataPackage * package, const char * filename)
{
    // check if sound is already available
    const std::string strFile(filename);
    const std::size_t fileId = GetFileId(strFile);

    Sound * sound = GetSound(fileId);

    if(sound != nullptr)
        return sound;

    // sound not found -> create it
    sound = new Sound(package, filename);

    if(sound->IsValid())
    {
        mSounds.emplace(fileId, sound);
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
    const std::string strFile(filename);
    const std::size_t fileId = GetFileId(strFile);

    return GetSound(fileId);
}

Sound * AudioManager::GetSound(std::size_t fileId)
{
    auto it = mSounds.find(fileId);

    if(it != mSounds.end())
        return it->second;
    else
        return nullptr;
}

// -- MUSIC --
Music * AudioManager::CreateMusic(const char * filename)
{
    // check if music is already available
    const std::string strFile(filename);
    const std::size_t fileId = GetFileId(strFile);

    Music * music = GetMusic(fileId);

    if(music != nullptr)
        return music;

    // music not found -> create it
    music = new Music(filename);

    if(music->IsValid())
    {
        mMusic.emplace(fileId, music);
        return music;
    }
    else
    {
        delete music;
        return nullptr;
    }
}

Music * AudioManager::CreateMusic(const core::DataPackage * package, const char * filename)
{
    // check if music is already available
    const std::string strFile(filename);
    const std::size_t fileId = GetFileId(strFile);

    Music * music = GetMusic(fileId);

    if(music != nullptr)
        return music;

    // music not found -> create it
    music = new Music(package, filename);

    if(music->IsValid())
    {
        mMusic.emplace(fileId, music);
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
    const std::string strFile(filename);
    const std::size_t fileId = GetFileId(strFile);

    return GetMusic(fileId);
}

Music * AudioManager::GetMusic(std::size_t fileId)
{
    auto it = mMusic.find(fileId);

    if(it != mMusic.end())
        return it->second;
    else
        return nullptr;
}

unsigned int AudioManager::GetVolumeAudio() const
{
    const int vol = Mix_MasterVolume(-1);
    return static_cast<int>(roundf(vol * 100.f / MIX_MAX_VOLUME));
}

unsigned int AudioManager::GetVolumeMusic() const
{
   const int vol = Mix_VolumeMusic(-1);
   return static_cast<int>(roundf(vol * 100.f / MIX_MAX_VOLUME));
}

unsigned int AudioManager::GetVolumeSound() const
{
    const int vol = Mix_Volume(-1, -1);
    return static_cast<int>(roundf(vol * 100.f / MIX_MAX_VOLUME));
}

void AudioManager::SetVolumeAudio(unsigned int perc)
{
    const int maxPerc = 100;

    if(perc > maxPerc)
        perc = maxPerc;

    const float fperc = static_cast<float>(perc);
    const int vol = static_cast<int>(roundf(MIX_MAX_VOLUME * fperc / maxPerc));
    Mix_MasterVolume(vol);
}

void AudioManager::SetVolumeMusic(unsigned int perc)
{
    const int maxPerc = 100;

    if(perc > maxPerc)
        perc = maxPerc;

    const float fperc = static_cast<float>(perc);
    const int vol = static_cast<int>(roundf(MIX_MAX_VOLUME * fperc / maxPerc));
    Mix_VolumeMusic(vol);
}

void AudioManager::SetVolumeSound(unsigned int perc)
{
    const int maxPerc = 100;

    if(perc > maxPerc)
        perc = maxPerc;

    const float fperc = static_cast<float>(perc);
    const int vol = static_cast<int>(roundf(MIX_MAX_VOLUME * fperc / maxPerc));
    Mix_Volume(-1, vol);
}

AudioManager::AudioManager()
    : mPlayer(new AudioPlayer(this))
{
    // init audio system
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

    // query audio system
    Mix_QuerySpec(&currFrequency, &currFormat, &currChannels);

    mSoundtracks = Mix_AllocateChannels(mSoundtracks);

    std::cout << "AudioManager OK - freq: " << currFrequency << "/" << frequency
              << " - form: " << currFormat << "/" << format
              << " - chan: " << currChannels << "/" << channels
              << " - sound tracks: " << mSoundtracks << std::endl;

    mValid = true;
}

AudioManager::~AudioManager()
{
    delete mPlayer;

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
