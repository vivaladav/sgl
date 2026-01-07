#include "sgl/utilities/StringManager.h"

#include "sgl/core/DataPackage.h"

#include <fstream>

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
    const std::string strData(data, size);
    const std::string NL("\n");

    std::size_t lineEnd = 0;
    std::size_t lineStart = 0;

    while((lineEnd = strData.find(NL, lineStart)) != std::string::npos)
    {
        std::size_t sizeLine = lineEnd - lineStart;

        // read key
        const std::size_t sizeKey = strData.find(' ', lineStart) - lineStart;
        std::string key;
        key.reserve(sizeKey);
        key = strData.substr(lineStart, sizeKey);

        // define text
        const std::size_t posText = lineStart + sizeKey + 1;
        const std::size_t sizeText = lineEnd - posText;
        std::string text;
        text.reserve(sizeText);
        text = strData.substr(posText, sizeText);

        // replace "\n" occurencies with new line character
        const std::string tagNL("\\n");
        const std::size_t lenTag = tagNL.length();

        std::size_t pos = 0;

        while((pos = text.find(tagNL, pos)) != std::string::npos)
            text.replace(pos++, lenTag, NL);

        // check if string is already stored
        auto it = mStrings.find(key);

        // update text
        if(it != mStrings.end())
            it->second = text;
        // insert text
        else
            mStrings.emplace(key, text);

        lineStart = ++lineEnd;
    }
}

} // namespace utilities
} // namespace sgl
