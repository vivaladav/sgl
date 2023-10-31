#pragma once

namespace sgl
{
namespace utilities
{

class HashCRC32
{
public:
    // compute the hash value for a string (NULL terminated)
    static unsigned int GetStringHash(const char * str);
    // compute the hash value for size bytes of data
    static unsigned int GetDataHash(const char * data, unsigned int size);
    // compute the hash value for a file
    static unsigned int GetFileHash(const char * path);

private:
    static const unsigned int HASH_TABLE[256];
};

} // namespace utilities
} // namespace sgl
