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

Sound::Sound(const char * filename)
{
    mData = Mix_LoadWAV(filename);

    if(nullptr == mData)
    {
        std::cout << "Sound::Sound ERROR: " << SDL_GetError() << std::endl;
        mValid = false;
        return ;
    }

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
