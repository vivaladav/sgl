#include "sgl/core/DataPackage.h"

#include <fstream>

namespace sgl
{
namespace core
{

 DataPackage::DataPackage(const char * filename)
 {
     const int sizeFile = GetFileSize(filename);

     if(sizeFile == 0)
         return ;

    std::ifstream ifs(filename, std::ios::binary);

    int totRead = 0;

    while(totRead < sizeFile)
    {
        // SIZE of file ID
        int sizeId = 0;
        int sizeRead = sizeof(sizeId);

        if(ifs.read(reinterpret_cast<char*>(&sizeId), sizeRead))
            totRead += sizeRead;
        else
            return;

        // file ID
        std::string fileId(sizeId, '\0');
        sizeRead = sizeId;

        if(ifs.read(&fileId[0], sizeRead))
            totRead += sizeRead;
        else
            return ;

        // SIZE of data
        int sizeData = 0;
        sizeRead = sizeof(sizeData);

        if(ifs.read(reinterpret_cast<char*>(&sizeData), sizeRead))
            totRead += sizeRead;
        else
            return ;

        // data
        auto data = new char[sizeData];
        sizeRead = sizeData;

        if(ifs.read(data, sizeRead))
            totRead += sizeRead;
        else
        {
            delete[] data;
            return ;
        }

        Data block {data, sizeData};
        mData.emplace(fileId, block);
    }

    mValid = true;
}

DataPackage::~DataPackage()
{
    for(auto & it : mData)
        delete[] it.second.data;
}

const char * DataPackage::GetData(const char * fileId) const
{
    auto it = mData.find(fileId);

    if(it != mData.end())
        return it->second.data;
    else
        return 0;
}

int DataPackage::GetDataSize(const char * fileId) const
{
    auto it = mData.find(fileId);

    if(it != mData.end())
        return it->second.size;
    else
        return 0;
}

int DataPackage::GetFileSize(const char * filename)
{
    std::ifstream f(filename, std::ios::ate);

    if(!f.good())
        return 0;
    else
        return f.tellg();
}

} // namespace core
} // namespace sgl
