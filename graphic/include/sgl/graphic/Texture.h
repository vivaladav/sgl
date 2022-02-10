#pragma once

#include "sgl/core/Rect.h"

#include <memory>

struct SDL_Rect;
struct SDL_Surface;
struct SDL_Texture;

namespace sgl
{
namespace graphic
{

class TextureData;

enum TextureScaleMode : int;
enum TextureQuality : int;

class Texture
{
public:
    Texture();
    Texture(SDL_Surface * data, TextureQuality q);
    Texture(const char * file, TextureQuality q);
    Texture(const std::shared_ptr<TextureData> & data);
    ~Texture();

    void SetData(const std::shared_ptr<TextureData> & data);
    bool HasData() const;

    int GetWidth() const;
    int GetHeight() const;

    void ResetSourceRect();
    void SetSourceRect(int x, int y, int w, int h);
    void SetSourceRect(const core::Rectd & rect);

    void SetAlpha(unsigned char a);
    void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    // NOTE this will affect all the textures generated from the same file
    // which means that setting a scale mode for 1 sprite will affect all the ones
    // sharing the same texture
    void SetScaleMode(int sm);

private:
    std::shared_ptr<TextureData> mTexData;
    SDL_Rect * mSrcRect = nullptr;

    // access private data
    friend class TexturedRenderable;
};

inline bool Texture::HasData() const { return mTexData != nullptr; }

} // namespace graphic
} // namespace sgl
