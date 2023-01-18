#pragma once

#include <functional>
#include <string>
#include <unordered_map>

namespace sgl
{

namespace core { class DataPackage; }

namespace media
{

class AudioPlayer;
class Music;
class Sound;

class AudioManager
{
public:
    static AudioManager * Create();
    static AudioManager * Instance();
    static void Destroy();

    bool IsValid() const;

    std::size_t GetFileId(const std::string & filename);

    AudioPlayer * GetPlayer() const;

    // -- SFX --
    Sound * CreateSound(const char * filename);
    Sound * CreateSound(const core::DataPackage * package, const char * filename);

    Sound * GetSound(const char * filename);
    Sound * GetSound(std::size_t fileId);

    // -- MUSIC --
    Music * CreateMusic(const char * filename);
    Music * CreateMusic(const core::DataPackage * package, const char * filename);

    Music * GetMusic(const char * filename);
    Music * GetMusic(std::size_t fileId);

    // -- VOLUME --
    unsigned int GetVolumeAudio() const;
    unsigned int GetVolumeMusic() const;
    unsigned int GetVolumeSound() const;

    void SetVolumeAudio(unsigned int perc);
    void SetVolumeMusic(unsigned int perc);
    void SetVolumeSound(unsigned int perc);

private:
    AudioManager();
    ~AudioManager();

private:
    static AudioManager * mInstance;

private:
    std::unordered_map<std::size_t, Music *> mMusic;
    std::unordered_map<std::size_t, Sound *> mSounds;

    AudioPlayer * mPlayer = nullptr;

    bool mValid = false;
};

inline AudioManager * AudioManager::Instance() { return mInstance; }

inline bool AudioManager::IsValid() const { return mValid; }

inline std::size_t AudioManager::GetFileId(const std::string & filename)
{
    return std::hash<std::string>{}(std::string(filename));
}

inline AudioPlayer * AudioManager::GetPlayer() const { return mPlayer; }

} // namespace media
} // namespace sgl
