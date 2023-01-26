#include "sgl/media/Music.h"

#include "sgl/core/DataPackage.h"

#ifdef LINUX
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
#else
    #include <SDL.h>
    #include <SDL_mixer.h>
#endif

#include <functional>
#include <iostream>

#define SYSTEM_MUSIC(ptr) static_cast<Mix_Music *>(ptr)

namespace sgl
{
namespace media
{

Music::Music(const char * filename)
    : mId(std::hash<std::string>{}(std::string(filename)))
{
    mData = Mix_LoadMUS(filename);

    if(nullptr == mData)
    {
        std::cout << "Music::Music(const char *) ERROR: " << SDL_GetError() << std::endl;
        mValid = false;
        return ;
    }

    mDuration = Mix_MusicDuration(SYSTEM_MUSIC(mData));

    std::cout << "Music::Music master volume: " << Mix_MasterVolume(-1) << std::endl;
    std::cout << "Music::Music channels volume: " << Mix_Volume(-1, -1) << std::endl;
    std::cout << "Music::Music music channel volume: " << Mix_VolumeMusic(-1) << std::endl;
    std::cout << "Music::Music music volume: " << Mix_GetMusicVolume(SYSTEM_MUSIC(mData)) << std::endl;
    std::cout << "Music::Music music duration (ms): " << mDuration * 1000.f << std::endl;

    mValid = true;
}

Music::Music(const core::DataPackage * package, const char * filename)
    : mId(std::hash<std::string>{}(std::string(filename)))
{
    // create shared data from package
    const char * data = package->GetData(filename);
    const int sizeData = package->GetDataSize(filename);

    if(!data)
    {
        std::cout << "Sound::Sound(DataPackage) - ERR: failed to get data from package for "
                  << filename << std::endl;
        return ;
    }

    // create music data
    mDataRW = SDL_RWFromConstMem(data, sizeData);
    mData = Mix_LoadMUS_RW(mDataRW, 0);

    if(nullptr == mData)
    {
        std::cout << "Music::Music(DataPackage) ERROR: " << SDL_GetError() << std::endl;
        mValid = false;
        return ;
    }

    mDuration = Mix_MusicDuration(SYSTEM_MUSIC(mData));

    std::cout << "Music::Music master volume: " << Mix_MasterVolume(-1) << std::endl;
    std::cout << "Music::Music channels volume: " << Mix_Volume(-1, -1) << std::endl;
    std::cout << "Music::Music music channel volume: " << Mix_VolumeMusic(-1) << std::endl;
    std::cout << "Music::Music music volume: " << Mix_GetMusicVolume(SYSTEM_MUSIC(mData)) << std::endl;
    std::cout << "Music::Music music duration (ms): " << mDuration * 1000.f << std::endl;

    mValid = true;
}

Music::~Music()
{
    if(mData)
      Mix_FreeMusic(SYSTEM_MUSIC(mData));

    if(mDataRW)
        SDL_RWclose(mDataRW);
}

bool Music::Play()
{
    if(Mix_PlayMusic(SYSTEM_MUSIC(mData), 0) == -1)
    {
        std::cout << "Music::Play ERROR: " << SDL_GetError() << std::endl;
        return false;
    }
    else
        return true;
}

} // namespace media
} // namespace sgl
