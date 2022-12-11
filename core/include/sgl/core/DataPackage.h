#pragma once

#include <string>
#include <unordered_map>

namespace sgl
{
namespace core
{

class DataPackage
{
public:
    DataPackage(const char * filename);
    ~DataPackage();

    char * GetData(const char * fileId) const;

    bool IsValid() const;

private:
    int GetFileSize(const char * filename);

private:
    std::unordered_map<std::string, char *> mData;

    bool mValid = false;
};

inline bool DataPackage::IsValid() const { return mValid; }

} // namespace core
} // namespace sgl
