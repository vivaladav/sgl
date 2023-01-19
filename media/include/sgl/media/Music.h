#pragma once

#include <cstddef>

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

    int GetDurationMs() const;

    bool IsValid() const;

    bool Play();

private:
    void * mData = nullptr;

    std::size_t mId = 0;

    int mDuration = 0;

    bool mValid = false;
};

inline std::size_t Music::GetId() const { return mId; }

inline int Music::GetDurationMs() const { return mDuration; }

inline bool Music::IsValid() const { return mValid; }

} // namespace media
} // namespace sgl
