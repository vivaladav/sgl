#pragma once

namespace sgl
{
namespace media
{

class AudioManager
{
public:
    static AudioManager * Create();
    static AudioManager * Instance();
    static void Destroy();

    bool IsValid() const;

    // -- SFX --
    bool PlaySound(const char * filename);

    // -- MUSIC --
    bool PlayMusic(const char * filename);
    void StopMusic();
    void FadeOutMusic(int ms);

private:
    AudioManager();
    ~AudioManager();

private:
    static AudioManager * mInstance;

private:
    bool mValid = false;
};

inline AudioManager * AudioManager::Instance() { return mInstance; }

inline bool AudioManager::IsValid() const { return mValid; }

} // namespace media
} // namespace sgl
