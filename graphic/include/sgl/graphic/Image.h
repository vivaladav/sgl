#pragma once

#include "sgl/graphic/TexturedRenderable.h"

namespace sgl
{
namespace graphic
{

class Image : public TexturedRenderable
{
public:
    Image();
    Image(const char * file);
    Image(Texture * tex);

    bool Load(const char * file);
};

inline Image::Image() { }

} // namespace graphic
} // namespace sgl
