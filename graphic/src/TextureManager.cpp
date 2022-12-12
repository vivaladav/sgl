#include "sgl/graphic/TextureManager.h"

#include "sgl/core/DataPackage.h"
#include "sgl/graphic/GraphicConstants.h"
#include "sgl/graphic/Texture.h"
#include "sgl/graphic/TextureData.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>

namespace sgl
{
namespace graphic
{

TextureManager *  TextureManager::mInstance = nullptr;

TextureManager * TextureManager::Create()
{
    if(!mInstance)
        mInstance = new TextureManager;

    return mInstance;
}

void TextureManager::Destroy()
{
    delete mInstance;
}

TextureManager::TextureManager()
    : mTexQuality(TextureQuality::GOOD)
{
}

void TextureManager::RegisterTexture(const core::DataPackage & package, const char * file)
{
    const std::string strFile(file);
    auto res = mTextures.find(strFile);

    // texture already created
    if(res != mTextures.end())
    {
        std::cout << "TextureManager::RegisterTexture - ERR: file from package " << file
                  << " already registered" << std::endl;
        return ;
    }

    // get data from package
    const char * data = package.GetData(file);
    const int sizeData = package.GetDataSize(file);

    if(!data)
        return ;

    SDL_RWops * rwdata = SDL_RWFromConstMem(data, sizeData);

    auto tex = new Texture(rwdata, mTexQuality);
    mTextures.emplace(strFile, tex);

    SDL_RWclose(rwdata);
}

Texture * TextureManager::GetTexture(const char * file)
{
    const std::string strFile(file);

    Texture * tex = nullptr;

    auto res = mTextures.find(strFile);

    if(res != mTextures.end())
        tex = res->second;
    else
    {
        tex = new Texture(file, mTexQuality);
        mTextures.emplace(strFile, tex);
    }

    return tex;
}

void TextureManager::DestroyTexture(const char * file)
{
    auto res = mTextures.find(std::string(file));

    if(res != mTextures.end())
        delete res->second;

    mTextures.erase(res);
}

void TextureManager::DestroyTextures()
{
    for(auto & item : mTextures)
        delete item.second;

    mTextures.clear();
}

void TextureManager::RegisterSprite(const char * file, const std::vector<core::Rectd> & srcRects)
{
    const std::string strFile(file);

    auto res = mSprites.find(strFile);

    // vector with Textures already created
    if(res != mSprites.end())
    {
        std::cout << "TextureManager::RegisterSprite - ERR: Sprite " << file
                  << " already registered" << std::endl;
        return ;
    }

    const unsigned int numRects = srcRects.size();

    std::vector<Texture *> textures;

    // create Textures with no data and add shared one
    std::shared_ptr<TextureData> data = std::make_shared<TextureData>(file, mTexQuality);

    for(unsigned int i = 0; i < numRects; ++i)
    {
        auto tex = new Texture;
        tex->SetSourceRect(srcRects[i]);
        tex->SetData(data);

        textures.push_back(tex);
    }

    // store textures in map
    mSprites.emplace(strFile, textures);
}

Texture * TextureManager::GetSprite(const char * file, unsigned int spriteId)
{
    const std::string strFile(file);

    // find atlas
    auto res = mSprites.find(strFile);

    // no atlas found
    if(mSprites.end() == res)
        return nullptr;

    const std::vector<Texture *> & textures = res->second;

    // no sprite found
    if(spriteId >= textures.size())
        return nullptr;

    return textures[spriteId];
}

void TextureManager::DestroySprites()
{
    for(auto & sprite : mSprites)
    {
        for(auto tex : sprite.second)
            delete tex;
    }

    mSprites.clear();
}

} // namespace graphic
} // namespace sgl
