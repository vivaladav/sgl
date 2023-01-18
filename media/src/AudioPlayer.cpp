#include "sgl/media/AudioPlayer.h"

#include "sgl/media/AudioManager.h"
#include "sgl/media/Music.h"
#include "sgl/media/Sound.h"

namespace sgl
{

namespace media
{
// -- MUSIC --
void AudioPlayer::PlayMusic(const char * filename)
{
    Music * music = mAm->GetMusic(filename);

    if(music)
        music->Play();
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
