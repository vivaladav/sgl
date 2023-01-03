#include "sgl/graphic/TextureData.h"

#include "sgl/graphic/GraphicConstants.h"
#include "sgl/graphic/Renderer.h"

#ifdef LINUX
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
#endif


#include <cassert>
#include <iostream>

namespace sgl
{
namespace graphic
{

TextureData::TextureData(SDL_Surface * data, TextureQuality q)
{
    assert(data);

    // sest quality BEFORE creating a new texture
    SetTextureQuality(q);

    mData = SDL_CreateTextureFromSurface(Renderer::Instance()->mSysRenderer, data);

    mWidth = data->w;
    mHeight = data->h;
}

TextureData::TextureData(SDL_RWops * rwdata, TextureQuality q)
{
    assert(rwdata);

    // sest quality BEFORE creating a new texture
    SetTextureQuality(q);

    mData = IMG_LoadTexture_RW(Renderer::Instance()->mSysRenderer, rwdata, 0);

    if(!mData)
    {
        std::cerr << "IMG_LoadTexture_RW: " << IMG_GetError() << std::endl;
        return ;
    }

    SDL_QueryTexture(mData, nullptr, nullptr, &mWidth, &mHeight);
}

TextureData::TextureData(const char * file, TextureQuality q)
    : mFilePath(file)
{
    assert(file);

    // sest quality BEFORE creating a new texture
    SetTextureQuality(q);

    mData = IMG_LoadTexture(Renderer::Instance()->mSysRenderer, file);

    if(!mData)
    {
        std::cerr << "IMG_LoadTexture_RW: " << IMG_GetError() << std::endl;
        return ;
    }

    SDL_QueryTexture(mData, nullptr, nullptr, &mWidth, &mHeight);
}

TextureData::~TextureData()
{
    SDL_DestroyTexture(mData);
}

void TextureData::SetAlpha(unsigned char a)
{
    SDL_SetTextureAlphaMod(mData, a);
}

void TextureData::SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    SDL_SetTextureColorMod(mData, r, g, b);
    SDL_SetTextureAlphaMod(mData, a);
}

void TextureData::SetScaleMode(int sm)
{
    SDL_SetTextureScaleMode(mData, static_cast<SDL_ScaleMode>(sm));
}

void TextureData::SetTextureQuality(TextureQuality q)
{
    if(TextureQuality::BEST == q)
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");    // anisotropic
    else if(TextureQuality::GOOD == q)
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");    // linear
    else
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");    // nearest pixel
}

} // namespace graphic
} // namespace sgl

