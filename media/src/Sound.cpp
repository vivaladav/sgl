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

    // create sound data
    mDataRW = SDL_RWFromConstMem(data, sizeData);
    mData = Mix_LoadWAV_RW(mDataRW, 0);

    if(nullptr == mData)
    {
        std::cout << "Sound::Sound(DataPackage) ERROR: " << SDL_GetError() << std::endl;
        mValid = false;
        return ;
    }

    mValid = true;
}

Sound::~Sound()
{
    if(mData)
        Mix_FreeChunk(mData);

    if(mDataRW)
        SDL_RWclose(mDataRW);
}

bool Sound::Play(unsigned int loops)
{
    return ExecutePlay(loops);
}

bool Sound::PlayLoop()
{
    return ExecutePlay(-1);
}

void Sound::FadeOut(int ms)
{
    if(mChannel < 0)
        return ;

    Mix_FadeOutChannel(mChannel, ms);

    mChannel = -1;
}

void Sound::Stop()
{
    if(mChannel < 0)
        return ;

    Mix_HaltChannel(mChannel);

    mChannel = -1;
}

bool Sound::ExecutePlay(int loops)
{
    mChannel = Mix_PlayChannel(-1, mData, loops);

    // TODO
    // handle play termination with Mix_ChannelFinished in Player
    // to clear the channel data

    if(mChannel == -1)
    {
        std::cout << "Sound::ExecutePlay ERROR: " << SDL_GetError() << std::endl;
        return false;
    }
    else
        return true;
}

} // namespace media
} // namespace sgl
