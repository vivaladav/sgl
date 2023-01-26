#pragma once

#include <cstddef>

struct SDL_RWops;

namespace sgl
{

namespace core { class DataPackage; }

namespace media
{

class Music
{
public:
    Music(const char * filename);
    Music(const core::DataPackage * package, const char * filename);
    ~Music();

    std::size_t GetId() const;

    float GetDurationSec() const;

    bool IsValid() const;

    bool Play();

private:
    SDL_RWops * mDataRW = nullptr;
    void * mData = nullptr;

    std::size_t mId = 0;

    float mDuration = 0.f;

    bool mValid = false;
};

inline std::size_t Music::GetId() const { return mId; }

inline float Music::GetDurationSec() const { return mDuration; }

inline bool Music::IsValid() const { return mValid; }

} // namespace media
} // namespace sgl
