#pragma once

#include "sgl/sgui/AbstractButton.h"

#include <string>

namespace sgl
{

namespace graphic
{
    class Font;
    class Renderable;
    class Texture;
}

namespace sgui
{

class PushButton : public AbstractButton
{
public:
    PushButton(Widget * parent = nullptr);

    void SetBackground(const char * file);
    void SetBackground(graphic::Texture * tex);

    void SetIcon(graphic::Texture * tex);
    void SetIconMargin(int m);

    void SetLabel(const char * text);
    void SetLabelFont(graphic::Font * font);

    void SetContentColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void SetContentColor(unsigned int color);

    const std::string & GetText() const;

protected:
    void SetCurrBg(graphic::Renderable * bg);
    void SetCurrIcon(graphic::Renderable * icon);
    void SetCurrLabel(graphic::Renderable * label);

    void HandlePositionChanged() override;

private:
    void PositionElements();

private:
    std::string mText;

    graphic::Font * mFontLabel = nullptr;

    // actual objects created by SetBackground, SetIcon and SetLabel
    graphic::Renderable * mBg = nullptr;
    graphic::Renderable * mIcon = nullptr;
    graphic::Renderable * mLabel = nullptr;

    // pointers to the current active objects
    graphic::Renderable * mCurrBg = nullptr;
    graphic::Renderable * mCurrIcon = nullptr;
    graphic::Renderable * mCurrLabel = nullptr;

    int mMarginIcon = 0;
};

inline const std::string & PushButton::GetText() const { return mText; }

inline void PushButton::SetIconMargin(int m)
{
    if(m != mMarginIcon)
    {
        mMarginIcon = m;
        PositionElements();
    }
}

} // namespace sgui
} // namespace sgl
