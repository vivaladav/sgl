#include "sgl/sgui/PushButton.h"

#include "sgl/core/event/MouseButtonEvent.h"
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
    : Widget(parent)
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

void PushButton::SetChecked(bool val)
{
    if(val != mChecked)
    {
        mChecked = val;
        HandleCheckedChanged(mChecked);

        for(auto & it : mOnToggle)
            it.second(mChecked);
    }
}

void PushButton::Click()
{
    // checkable button
    if(mCheckable)
    {
        mChecked = !mChecked;

        HandleCheckedChanged(mChecked);

        for(auto & it : mOnToggle)
            it.second(mChecked);
    }
    // standard button
    else
        for(auto & it: mOnClick)
            it.second();
}

unsigned int PushButton::AddOnClickFunction(const std::function<void()> & f)
{
    static unsigned int num = 0;

    int fId = ++num;
    mOnClick.emplace(fId, f);

    return fId;
}

void PushButton::RemoveClickFunction(unsigned int fId)
{
    auto it = mOnClick.find(fId);

    if(it != mOnClick.end())
        mOnClick.erase(it);
}

unsigned int PushButton::AddOnToggleFunction(const std::function<void(bool)> & f)
{
    static unsigned int num = 0;

    int fId = ++num;
    mOnToggle.emplace(fId, f);

    return fId;
}

void PushButton::RemoveToggleFunction(unsigned int fId)
{
    auto it = mOnToggle.find(fId);

    if(it != mOnToggle.end())
        mOnToggle.erase(it);
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

void PushButton::HandleStateEnabled()
{
    if(IsChecked())
        SetState(CHECKED);
    else
        SetState(NORMAL);
}
void PushButton::HandleStateDisabled()
{
     SetState(DISABLED);
}

void PushButton::HandleMouseButtonDown(sgl::core::MouseButtonEvent & event)
{
    if(!IsEnabled())
        return ;

    HandleButtonDown();

    event.SetConsumed();
}

void PushButton::HandleMouseButtonUp(core::MouseButtonEvent & event)
{
    if(!IsEnabled())
        return ;

    HandleButtonUp();

    event.SetConsumed();
}

void PushButton::HandleMouseOver()
{
    if(!IsEnabled() || IsChecked())
        return ;

    SetState(MOUSE_OVER);
}

void PushButton::HandleMouseOut()
{
    if(!IsEnabled() || IsChecked())
        return ;

    SetState(NORMAL);
}

void PushButton::HandleCheckedChanged(bool checked)
{
    SetState(checked ? CHECKED : NORMAL);
}

void PushButton::OnStateChanged(VisualState state) { }

void PushButton::HandleButtonDown()
{
    if(IsCheckable())
        SetState(CHECKED);
    else
        SetState(PUSHED);
}

void PushButton::HandleButtonUp()
{
    // do not uncheck if exclusive (in button group)
    if(mExclusive && mChecked)
        return ;

    // set default state then handle click
    if(IsMouseOver())
        SetState(MOUSE_OVER);
    else
        SetState(NORMAL);

    Click();
}

void PushButton::SetState(VisualState state)
{
    if(mState == state)
        return ;

    mState = state;

    OnStateChanged(state);
}

void PushButton::PositionLabel()
{
    const int x = GetScreenX() + (GetWidth() - mCurrLabel->GetWidth()) * 0.5f;
    const int y = GetScreenY() + (GetHeight() - mCurrLabel->GetHeight()) * 0.5f;

    mCurrLabel->SetPosition(x, y);
}

} // namespace sgui
} // namespace sgl
