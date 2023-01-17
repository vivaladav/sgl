#include "sgl/media/Music.h"

#ifdef LINUX
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
#else
    #include <SDL.h>
    #include <SDL_mixer.h>
#endif

#include <iostream>

#define SYSTEM_MUSIC(ptr) static_cast<Mix_Music *>(ptr)

namespace sgl
{
namespace media
{

Music::Music(const char * filename)
{
    mData = Mix_LoadMUS(filename);

    if(nullptr == mData)
    {
        std::cout << "Music::Music ERROR: " << SDL_GetError() << std::endl;
        mValid = false;
        return ;
    }

    std::cout << "Music::Music master volume: " << Mix_MasterVolume(-1) << std::endl;
    std::cout << "Music::Music channels volume: " << Mix_Volume(-1, -1) << std::endl;
    std::cout << "Music::Music music channel volume: " << Mix_VolumeMusic(-1) << std::endl;
    std::cout << "Music::Music music volume: " << Mix_GetMusicVolume(SYSTEM_MUSIC(mData)) << std::endl;
    std::cout << "Music::Music music duration: " << Mix_MusicDuration(SYSTEM_MUSIC(mData)) << std::endl;

    mValid = true;
}

Music::~Music()
{
    if(mData)
      Mix_FreeMusic(SYSTEM_MUSIC(mData));
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
