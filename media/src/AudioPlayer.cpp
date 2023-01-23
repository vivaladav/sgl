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
    // do not play when music is disabled
    if(!mMusicEnabled)
        return ;

    const std::size_t musicId = mAm->GetFileId(filename);

    // music already playing and caller doesn't want to restart
    if(!restartSame && musicId == mMusicPlayingId)
        return ;

    Music * music = mAm->GetMusic(musicId);

    if(nullptr == music)
        return ;

    mMusicPlayingId = musicId;
    mMusicPlaying = true;
    mPlayingDurationLeft = music->GetDurationSec();

    music->Play();
}

void AudioPlayer::PauseMusic()
{
    // do not pause when music is disabled or not playing
    if(!mMusicEnabled || !mMusicPlaying || 0 == mMusicPlayingId)
        return ;

    mMusicPlaying = false;

    Mix_PauseMusic();
}

void AudioPlayer::ResumeMusic()
{
    // do not play when music is disabled or already playing or no music was playing
    if(!mMusicEnabled || mMusicPlaying || 0 == mMusicPlayingId)
        return ;

    mMusicPlaying = true;

    Mix_ResumeMusic();
}

void AudioPlayer::StopMusic()
{
    Mix_HaltMusic();

    mMusicPlaying = false;

    mMusicPlayingId = 0;
}

void AudioPlayer::SetMusicEnabled(bool val)
{
    // nothing changed
    if(val == mMusicEnabled)
        return ;

    mMusicEnabled = val;

    // stop music if playing
    if(!mMusicEnabled && mMusicPlayingId != 0)
        StopMusic();
}

// -- SOUNDS --
void AudioPlayer::PlaySound(const char * filename)
{
    // do not play when sounds are disabled
    if(!mSoundEnabled)
        return ;

    Sound * sound = mAm->GetSound(filename);

    if(sound)
        sound->Play();
}

void AudioPlayer::PauseSounds()
{
    // do not pause when sounds are disabled
    if(!mSoundEnabled)
        return ;

    Mix_Pause(-1);
}

void AudioPlayer::ResumeSounds()
{
    // do not resume when sounds are disabled
    if(!mSoundEnabled)
        return ;

    Mix_Resume(-1);
}

void AudioPlayer::StopSounds()
{
    Mix_HaltChannel(-1);
}

void AudioPlayer::SetSoundEnabled(bool val)
{
    // nothing changed
    if(val == mSoundEnabled)
        return ;

    mSoundEnabled = val;

    // stop music if playing
    if(!mSoundEnabled)
        StopSounds();
}

void AudioPlayer::Update(float delta)
{
    // nothing to do if music is not playing
    if(!mMusicPlaying)
        return ;

    mPlayingDurationLeft -= delta;

    const float minDelta = 0.01f;

    if(mPlayingDurationLeft < minDelta)
    {
        mMusicPlayingId = 0;
        mMusicPlaying = false;
    }
}

} // namespace media
} // namespace sgl
