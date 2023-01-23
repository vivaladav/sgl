#pragma once

#include <vector>

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
    void PlayMusic(std::size_t musicId, bool restartSame = false);
    void PauseMusic();
    void ResumeMusic();
    void StopMusic();

    bool IsMusicEnabled() const;
    void SetMusicEnabled(bool val);

    // -- MUSIC PLAYLIST --
    void AddMusicToQueue(const char * filename);
    void ClearMusicQueue();
    void PlayMusicQueue();

    // -- SOUNDS --
    void PlaySound(const char * filename);
    void PauseSounds();
    void ResumeSounds();
    void StopSounds();

    bool IsSoundEnabled() const;
    void SetSoundEnabled(bool val);

    void Update(float delta);

private:
    AudioPlayer(AudioManager * am);
    ~AudioPlayer() = default;

private:
    std::vector<std::size_t> mQueue;
    unsigned int mQueueInd = 0;

    AudioManager * mAm = nullptr;

    std::size_t mMusicPlayingId = 0;
    float mPlayingDurationLeft = 0.f;

    bool mMusicPlaying = false;
    bool mMusicQueuePlaying = false;
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
