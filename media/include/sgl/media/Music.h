#pragma once

namespace sgl
{
namespace media
{

class Music
{
public:
    Music(const char * filename);
    ~Music();

    bool IsValid() const;

    bool Play();

private:
    void * mData = nullptr;

    bool mValid = false;
};

inline bool Music::IsValid() const { return mValid; }

} // namespace media
} // namespace sgl
