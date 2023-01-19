#include "sgl/media/AudioPlayer.h"

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

namespace sgl
{

namespace media
{
// -- MUSIC --
void AudioPlayer::PlayMusic(const char * filename, bool restartSame)
{
    const std::size_t musicId = mAm->GetFileId(filename);

    // music already playing and caller doesn't want to restart
    if(!restartSame && musicId == mMusicPlayingId)
        return ;

    Music * music = mAm->GetMusic(musicId);

    if(nullptr == music)
        return ;

    mMusicPlayingId = musicId;

    music->Play();
}

void AudioPlayer::PauseMusic()
{
    Mix_PauseMusic();
}

void AudioPlayer::ResumeMusic()
{
    Mix_ResumeMusic();
}

void AudioPlayer::StopMusic()
{
    Mix_HaltMusic();
}

// -- SOUNDS --
void AudioPlayer::PlaySound(const char * filename)
{
    Sound * sound = mAm->GetSound(filename);

    if(sound)
        sound->Play();
}

} // namespace media
} // namespace sgl
