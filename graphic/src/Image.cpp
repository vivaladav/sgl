#include "sgl/graphic/Image.h"

#include "sgl/graphic/Texture.h"
#include "sgl/graphic/TextureManager.h"

#include <cassert>

namespace sgl
{
namespace graphic
{

Image::Image(const char * file)
    : Image()
{
    Load(file);
}

Image::Image(Texture * tex)
{
    assert(tex);

    SetTexture(tex);
}

bool Image::Load(const char * file)
{
    assert(file);

    Texture * tex = TextureManager::Instance()->GetTexture(file);

    if(!tex)
        return false;

    SetTexture(tex);

    return true;
}


} // namespace graphic
} // namespace sgl
