#include "sgl/graphic/FontManager.h"

#include "sgl/core/DataPackage.h"
#include "sgl/graphic/Font.h"

#ifdef LINUX
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

#include <iostream>

namespace sgl
{
namespace graphic
{

FontManager * FontManager::mInstance = nullptr;

FontManager * FontManager::Create()
{
    if(!mInstance)
        mInstance = new FontManager;

    return mInstance;
}

void FontManager::Destroy()
{
    delete mInstance;
    mInstance = nullptr;
}

void FontManager::RegisterFont(const core::DataPackage & package, const char * file)
{
    const std::string strFile(file);
    auto res = mFontsData.find(strFile);

    // data already created
    if(res != mFontsData.end())
    {
        std::cout << "FontManager::RegisterFont - ERR: file from package " << file
                  << " already registered" << std::endl;
        return ;
    }

    const char * data = package.GetData(file);
    const int sizeData = package.GetDataSize(file);

    if(!data)
    {
        std::cout << "FontManager::RegisterFont - ERR: failed to get data from package for "
                  << file << std::endl;
        return ;
    }

    SDL_RWops * rwdata = SDL_RWFromConstMem(data, sizeData);

    mFontsData.emplace(strFile, rwdata);
}

Font * FontManager::GetFont(const char * file, int size, int style)
{
    // search if fonts already exists
    const std::string key = std::string(file) +
                            "sz" + std::to_string(size) +
                            "st" + std::to_string(style);

    auto res = mFonts.find(key);

    if(res != mFonts.end())
        return res->second;



    // font not found -> create it from existing data if available
    Font * font = nullptr;

    auto resData = mFontsData.find(file);

    if(resData != mFontsData.end())
        font = new Font(resData->second, size, style);
    // no existing data, try to create the font from file
    else
        font = new Font(file, size, style);

    if(!font->IsValid())
    {
        delete font;
        return nullptr;
    }

    mFonts.emplace(key, font);

    return font;
}

void FontManager::ClearFonts()
{
    // delete font data
    for(auto & it : mFontsData)
        SDL_RWclose(it.second);

    mFontsData.clear();

    // delete fonts
    for(auto & it : mFonts)
        delete it.second;

    mFonts.clear();
}

} // namespace graphic
} // namespace sgl
