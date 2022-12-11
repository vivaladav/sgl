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

    int sizeRead = 0;

    while(sizeRead < sizeFile)
    {
        // SIZE of file ID
        int sizeId = 0;
        int sizeRead = sizeof(sizeId);

        if(ifs.read(reinterpret_cast<char*>(&sizeId), sizeRead))
            sizeRead += sizeRead;
        else
            return;

        // file ID
        std::string fileId(sizeId, '\0');
        sizeRead = sizeId;

        if(ifs.read(&fileId[0], sizeRead))
            sizeRead += sizeRead;
        else
            return ;

        // SIZE of data
        int sizeData = 0;
        sizeRead = sizeof(sizeData);

        if(ifs.read(reinterpret_cast<char*>(&sizeData), sizeRead))
            sizeRead += sizeRead;
        else
            return ;

        // data
        auto data = new char[sizeData];
        sizeRead = sizeData;

        if(ifs.read(data, sizeData))
                sizeRead += sizeRead;
        else
        {
            delete[] data;
            return ;
        }

        mData.emplace(fileId, data);
    }


    mValid = true;
}

DataPackage::~DataPackage()
{
    for(auto & it : mData)
        delete it.second;
}

char * DataPackage::GetData(const char * fileId) const
{
    char * data = nullptr;

    return data;
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
