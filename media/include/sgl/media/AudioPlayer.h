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
    void PauseMusic();
    void ResumeMusic();
    void StopMusic();

    bool IsMusicEnabled() const;
    void SetMusicEnabled(bool val);

    // -- SOUNDS --
    void PlaySound(const char * filename);
    void PauseSounds();
    void ResumeSounds();
    void StopSounds();

    bool IsSoundEnabled() const;
    void SetSoundEnabled(bool val);

private:
    AudioPlayer(AudioManager * am);
    ~AudioPlayer() = default;

private:
    AudioManager * mAm = nullptr;

    std::size_t mMusicPlayingId = 0;

    bool mMusicEnabled = true;
    bool mSoundEnabled = true;

    // only AudioManager can create and delete this
    friend class AudioManager;
};

inline bool AudioPlayer::IsMusicEnabled() const { return mMusicEnabled; }
inline bool AudioPlayer::IsSoundEnabled() const { return mSoundEnabled; }

inline AudioPlayer::AudioPlayer(AudioManager * am) : mAm(am) { }

} // namespace media
} // namespace sgl
