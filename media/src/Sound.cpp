#include "sgl/media/Sound.h"

#include "sgl/core/DataPackage.h"

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

Sound::Sound(const char * filename)
    : mId(std::hash<std::string>{}(std::string(filename)))
{
    mData = Mix_LoadWAV(filename);

    if(nullptr == mData)
    {
        std::cout << "Sound::Sound(const char *) ERROR: " << SDL_GetError() << std::endl;
        mValid = false;
        return ;
    }

    std::cout << "Sound::Sound master volume: " << Mix_MasterVolume(-1) << std::endl;
    std::cout << "Sound::Sound channels volume: " << Mix_Volume(-1, -1) << std::endl;
    std::cout << "Sound::Sound chunk volume: " << Mix_VolumeChunk(mData, -1) << std::endl;

    mValid = true;
}

Sound::Sound(const core::DataPackage * package, const char * filename)
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

    SDL_RWops * rwdata = SDL_RWFromConstMem(data, sizeData);

    // create sound data
    mData = Mix_LoadWAV_RW(rwdata, 0);

    if(nullptr == mData)
    {
        std::cout << "Sound::Sound(DataPackage) ERROR: " << SDL_GetError() << std::endl;
        mValid = false;
        return ;
    }

    std::cout << "Sound::Sound num channels: " << Mix_AllocateChannels(-1) << std::endl;
    std::cout << "Sound::Sound master volume: " << Mix_MasterVolume(-1) << std::endl;
    std::cout << "Sound::Sound channels volume: " << Mix_Volume(-1, -1) << std::endl;
    std::cout << "Sound::Sound chunk volume: " << Mix_VolumeChunk(mData, -1) << std::endl;

    mValid = true;
}

Sound::~Sound()
{
    if(mData)
        Mix_FreeChunk(mData);
}

bool Sound::Play()
{
    if(Mix_PlayChannel(-1, mData, 0) == -1)
    {
        std::cout << "Sound::Play ERROR: " << SDL_GetError() << std::endl;
        return false;
    }
    else
        return true;
}

} // namespace media
} // namespace sgl
