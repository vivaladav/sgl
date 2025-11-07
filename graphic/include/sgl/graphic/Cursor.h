#pragma once

#include "TexturedRenderable.h"

namespace sgl
{
namespace graphic
{

class Texture;

class Cursor : public TexturedRenderable
{
public:
    // (hotX, hotY) is the point of the texture that corresponds to the actual
    // mouse position or the point where a click happens
    Cursor(Texture * tex, int hotX, int hotY);

    void Render() override;

private:
    int mHotX = 0;
    int mHotY = 0;
};

} // namespace graphic
} // namespace sgl
