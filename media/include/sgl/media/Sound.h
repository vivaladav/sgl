#pragma once

struct Mix_Chunk;

namespace sgl
{

namespace core { class DataPackage; }

namespace media
{

class Sound
{
public:
    Sound(const char * filename);
    Sound(const core::DataPackage * package, const char * filename);
    ~Sound();

    bool IsValid() const;

    bool Play();

private:
    Mix_Chunk * mData = nullptr;

    bool mValid = false;
};

inline bool Sound::IsValid() const { return mValid; }

} // namespace media
} // namespace sgl
