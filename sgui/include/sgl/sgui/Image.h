#pragma once

#include "sgl/sgui/Widget.h"

#include <string>

namespace sgl
{

namespace graphic
{
    class Renderable;
    class Texture;
}

namespace sgui
{

class Image : public Widget
{
public:
    Image(Widget * parent = nullptr);
    Image(const char * file, Widget * parent = nullptr);
    Image(graphic::Texture * tex, Widget * parent = nullptr);

    void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void SetColor(unsigned int color);

    void LoadImage(const char * file);

private:
    void HandlePositionChanged() override;

private:
    graphic::Renderable * mImg = nullptr;
};

} // namespace sgui
} // namespace sgl
