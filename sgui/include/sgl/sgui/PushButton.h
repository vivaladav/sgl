#pragma once

#include "sgl/sgui/AbstractButton.h"

#include <functional>
#include <map>
#include <string>

namespace sgl
{

namespace graphic
{
    class Font;
    class Renderable;
}

namespace sgui
{

class PushButton : public AbstractButton
{
public:
    PushButton(Widget * parent = nullptr);

    void SetBackground(const char * file);

    void SetLabel(const char * text);
    void SetLabelColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void SetLabelColor(unsigned int color);
    void SetLabelFont(graphic::Font * font);

    const std::string & GetText() const;

protected:
    void SetCurrBg(graphic::Renderable * bg);
    void SetCurrLabel(graphic::Renderable * label);

    void HandlePositionChanged() override;

private:
    void PositionLabel();

private:
    std::string mText;

    graphic::Font * mFontLabel = nullptr;

    // actual objects created by SetBackground and SetLabel
    graphic::Renderable * mBg = nullptr;
    graphic::Renderable * mLabel = nullptr;

    // pointers to the current active objects
    graphic::Renderable * mCurrBg = nullptr;
    graphic::Renderable * mCurrLabel = nullptr;
};

inline const std::string & PushButton::GetText() const { return mText; }

} // namespace sgui
} // namespace sgl
