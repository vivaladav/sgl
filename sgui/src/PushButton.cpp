#include "sgl/sgui/PushButton.h"

#include "sgl/graphic/DummyRenderable.h"
#include "sgl/graphic/Image.h"
#include "sgl/graphic/Text.h"
#include "sgl/sgui/Stage.h"

#include <cassert>

namespace sgl
{
namespace sgui
{

PushButton::PushButton(Widget * parent)
    : AbstractButton(parent)
    , mFontLabel(Stage::Instance()->GetDefaultFont())
    , mBg(new graphic::DummyRenderable)
    , mLabel(new graphic::DummyRenderable)
    , mCurrBg(mBg)
    , mCurrLabel(mLabel)
{
    RegisterRenderable(mBg);
    RegisterRenderable(mLabel);
}

void PushButton::SetBackground(const char * file)
{
    assert(file);

    UnregisterRenderable(mBg);
    delete mBg;

    mBg = new graphic::Image(file); // TODO check if Image is valid after creation and fallback on dummy
    RegisterRenderable(mBg);

    SetCurrBg(mBg);
}

void PushButton::SetLabel(const char * text)
{
    const std::string txt = text;

    // same text -> nothing to do
    if(txt == mText)
        return ;

    mText = text;

    const unsigned int col = mCurrLabel->GetColor();

    UnregisterRenderable(mLabel);
    delete mLabel;

    if(mText.empty())
        mLabel = new graphic::DummyRenderable;
    else
        mLabel = new graphic::Text(text, mFontLabel);

    RegisterRenderable(mLabel);

    mLabel->SetColor(col);

    SetCurrLabel(mLabel);
}

void PushButton::SetLabelColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    a = MixAlphaAndAlpha(a);

    mCurrLabel->SetColor(r, g, b, a);
}

void PushButton::SetLabelColor(unsigned int color)
{
    color = MixColorAndAlpha(color);

    mCurrLabel->SetColor(color);
}

void PushButton::SetLabelFont(graphic::Font * font)
{
    if(!font)
        return ;

    // same font -> nothing to do
    if(font == mFontLabel)
        return ;

    mFontLabel = font;

    // when changing font, update the label if already set
    if(!mText.empty())
    {
        const unsigned int col = mCurrLabel->GetColor();

        UnregisterRenderable(mLabel);
        delete mLabel;

        mLabel = new graphic::Text(mText.c_str(), mFontLabel);
        RegisterRenderable(mLabel);

        mLabel->SetColor(col);

        SetCurrLabel(mLabel);
    }
}

void PushButton::SetCurrBg(graphic::Renderable * bg)
{
    mCurrBg = bg;

    mCurrBg->SetPosition(GetScreenX(), GetScreenY());

    const int w = mCurrBg->GetWidth();
    const int h = mCurrBg->GetHeight();
    SetSize(w, h);
}

void PushButton::SetCurrLabel(graphic::Renderable * label)
{
    mCurrLabel = label;

    PositionLabel();
}

void PushButton::HandlePositionChanged()
{
    mCurrBg->SetPosition(GetScreenX(), GetScreenY());

    PositionLabel();
}

void PushButton::PositionLabel()
{
    const int x = GetScreenX() + (GetWidth() - mCurrLabel->GetWidth()) * 0.5f;
    const int y = GetScreenY() + (GetHeight() - mCurrLabel->GetHeight()) * 0.5f;

    mCurrLabel->SetPosition(x, y);
}

} // namespace sgui
} // namespace sgl
