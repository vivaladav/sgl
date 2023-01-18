#pragma once

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
    void PlayMusic(const char * filename);

    // -- SOUNDS --
    void PlaySound(const char * filename);

private:
    AudioPlayer(AudioManager * am);
    ~AudioPlayer() = default;

private:
    AudioManager * mAm = nullptr;

    // only AudioManager can create and delete this
    friend class AudioManager;
};

inline AudioPlayer::AudioPlayer(AudioManager * am) : mAm(am) { }

} // namespace media
} // namespace sgl
