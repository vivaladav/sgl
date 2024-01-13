#include "sgl/sgui/Image.h"

#include "sgl/graphic/DummyRenderable.h"
#include "sgl/graphic/Image.h"

#include <cassert>

namespace sgl
{
namespace sgui
{

Image::Image(Widget * parent)
    : Widget(parent)
    , mImg(new graphic::DummyRenderable)
{
    RegisterRenderable(mImg);
}

Image::Image(const char * file, Widget * parent)
    : Widget(parent)
{
    assert(file);

    LoadImage(file);
}

Image::Image(graphic::Texture * tex, Widget * parent)
    : Widget(parent)
    , mImg(new graphic::Image(tex))
    , mDummy(false)
{
    assert(tex);

    RegisterRenderable(mImg);

    SetSize(mImg->GetWidth(), mImg->GetHeight());

    mImg->SetPosition(GetScreenX(), GetScreenY());
}

void Image::SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    a = MixAlphaAndAlpha(a);

    mImg->SetColor(r, g, b, a);
}

void Image::SetColor(unsigned int color)
{
    color = MixColorAndAlpha(color);

    mImg->SetColor(color);
}

void Image::LoadImage(const char * file)
{
    graphic::Renderable * oldImg = mImg;

    mImg = new graphic::Image(file);

    RegisterRenderable(mImg);

    if(oldImg)
    {
        mImg->SetPosition(oldImg->GetX(), oldImg->GetY());
        mImg->SetColor(oldImg->GetColor());

        UnregisterRenderable(oldImg);

        delete oldImg;
    }

    SetSize(mImg->GetWidth(), mImg->GetHeight());

    mDummy = false;
}

void Image::SetTexture(graphic::Texture * tex)
{
    if(mDummy)
    {
        graphic::Renderable * oldImg = mImg;

        mImg = new graphic::Image(tex);

        RegisterRenderable(mImg);

        if(oldImg)
        {
            mImg->SetPosition(oldImg->GetX(), oldImg->GetY());
            mImg->SetColor(oldImg->GetColor());

            UnregisterRenderable(oldImg);

            delete oldImg;
        }

        mDummy = false;
    }
    else
        static_cast<graphic::Image *>(mImg)->SetTexture(tex);

    SetSize(mImg->GetWidth(), mImg->GetHeight());
}

void Image::HandlePositionChanged()
{
    mImg->SetPosition(GetScreenX(), GetScreenY());
}

} // namespace sgui
} // namespace sgl
