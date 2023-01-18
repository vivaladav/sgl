#pragma once

#include <cstddef>

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

    std::size_t GetId() const;

    bool IsValid() const;

    bool Play();

private:
    Mix_Chunk * mData = nullptr;

    std::size_t mId = 0;

    bool mValid = false;
};

inline std::size_t Sound::GetId() const { return mId; }

inline bool Sound::IsValid() const { return mValid; }

} // namespace media
} // namespace sgl
