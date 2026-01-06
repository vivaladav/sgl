#include "sgl/utilities/StringManager.h"

#include "sgl/core/DataPackage.h"

#include <fstream>
#include <sstream>

namespace sgl
{
namespace utilities
{

StringManager *  StringManager::mInstance = nullptr;

// ===== STATIC MEMBERS ======
StringManager * StringManager::Create()
{
    if(mInstance == nullptr)
        mInstance = new StringManager;

    return mInstance;
}

void StringManager::Destroy()
{
    delete mInstance;
    mInstance = nullptr;
}

// ===== PUBLIC  MEMBERS ======
bool StringManager::RegisterPackage(const char * file)
{
    if(mPackage != nullptr)
        return false;

    mPackage = new core::DataPackage(file);

    return true;
}

bool StringManager::LoadStringsFromFile(const char * file)
{
    // open  file
    std::ifstream fs(file, std::ios::binary | std::ios::ate);

    if(!fs.is_open())
        return false;

    const std::size_t size = fs.tellg();
    fs.seekg(0);

    char data[size];

    if(fs.read(data, size))
        LoadStringsData(data, size);

    fs.close();

    return true;
}

bool StringManager::LoadStringsFromPackage(const char * file)
{
    if(mPackage == nullptr)
        return false;

    const char * data = mPackage->GetData(file);
    const int sizeData = mPackage->GetDataSize(file);

    if(data == nullptr || sizeData == 0)
        return false;

    LoadStringsData(data, sizeData);

    return true;
}

const std::string & StringManager::GetString(const std::string & sid) const
{
    static const std::string unknown("?????");

    auto res = mStrings.find(sid);

    if(res != mStrings.end())
        return res->second;
    else
        return unknown;
}

// ===== PRIVATE  MEMBERS ======
StringManager::~StringManager()
{
    delete mPackage;
}

void StringManager::LoadStringsData(const char * data, unsigned int size)
{
    std::istringstream dataStream(data);

    std::string line;

    while(std::getline(dataStream, line))
    {
        std::istringstream lineStream(line);

        std::string key;
        lineStream >> key;

        std::string text;
        lineStream >> text;

        // check if string is already stored
        auto it = mStrings.find(key);

        // update text
        if(it != mStrings.end())
            it->second = text;
        // insert text
        else
            mStrings.emplace(key, text);
    }
}

} // namespace utilities
} // namespace sgl
