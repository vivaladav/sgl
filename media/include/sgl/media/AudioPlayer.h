#pragma once

#include <cstddef>

namespace sgl
{
namespace media
{

class AudioManager;
class Music;
class Sound;

class AudioPlayer
{
public:
    // -- MUSIC --
    void PlayMusic(const char * filename, bool restartSame = false);

    // -- SOUNDS --
    void PlaySound(const char * filename);

private:
    AudioPlayer(AudioManager * am);
    ~AudioPlayer() = default;

private:
    AudioManager * mAm = nullptr;

    std::size_t mMusicPlayingId = 0;

    // only AudioManager can create and delete this
    friend class AudioManager;
};

inline AudioPlayer::AudioPlayer(AudioManager * am) : mAm(am) { }

} // namespace media
} // namespace sgl
