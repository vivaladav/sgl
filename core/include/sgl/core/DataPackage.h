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

    const char * GetData(const char * fileId) const;
    int GetDataSize(const char * fileId) const;

    bool IsValid() const;

private:
    int GetFileSize(const char * filename);

private:
    struct Data
    {
        Data(char * d, int s) : data(d), size(s) {}

        const char * data = nullptr;
        int size = 0;
    };

    std::unordered_map<std::string, Data> mData;

    bool mValid = false;
};

inline bool DataPackage::IsValid() const { return mValid; }

} // namespace core
} // namespace sgl
