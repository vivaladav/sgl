#pragma once

#include <string>
#include <unordered_map>

namespace sgl
{
namespace media
{

class Music;
class Sound;

class AudioManager
{
public:
    static AudioManager * Create();
    static AudioManager * Instance();
    static void Destroy();

    bool IsValid() const;

    // -- SFX --
    Sound * CreateSound(const char * filename);
    Sound * GetSound(const char * filename);

    // -- MUSIC --
    Music * CreateMusic(const char * filename);
    Music * GetMusic(const char * filename);

    void StopMusic();
    void FadeOutMusic(int ms);

private:
    AudioManager();
    ~AudioManager();

private:
    static AudioManager * mInstance;

private:
    std::unordered_map<std::string, Music *> mMusic;
    std::unordered_map<std::string, Sound *> mSounds;

    bool mValid = false;
};

inline AudioManager * AudioManager::Instance() { return mInstance; }

inline bool AudioManager::IsValid() const { return mValid; }

} // namespace media
} // namespace sgl
