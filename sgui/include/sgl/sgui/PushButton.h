#pragma once

#include "sgl/sgui/Widget.h"

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

class PushButton : public Widget
{
public:
    enum VisualState : int
    {
        NORMAL = 0,
        DISABLED,
        MOUSE_OVER,
        PUSHED,
        CHECKED,

        NUM_VISUAL_STATES,

        NULL_STATE
    };

public:
    PushButton(Widget * parent = nullptr);

    void SetBackground(const char * file);

    void SetLabel(const char * text);
    void SetLabelColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void SetLabelColor(unsigned int color);
    void SetLabelFont(graphic::Font * font);

    bool IsCheckable() const;
    void SetCheckable(bool val);
    bool IsChecked() const;
    void SetChecked(bool val);
    bool IsExclusive() const;
    void SetExclusive(bool val);

    void Click();

    unsigned int AddOnClickFunction(const std::function<void()> & f);
    void RemoveClickFunction(unsigned int fId);
    unsigned int AddOnToggleFunction(const std::function<void(bool)> & f);
    void RemoveToggleFunction(unsigned int fId);

    const std::string & GetText() const;

    VisualState GetState() const;

protected:
    void SetCurrBg(graphic::Renderable * bg);
    void SetCurrLabel(graphic::Renderable * label);

    void HandleStateEnabled() override;
    void HandleStateDisabled() override;

    void HandleMouseButtonDown(sgl::core::MouseButtonEvent & event) override;
    void HandleMouseButtonUp(sgl::core::MouseButtonEvent & event) override;

    void HandleMouseOver() override;
    void HandleMouseOut() override;

    void HandlePositionChanged() override;

    void HandleButtonDown();
    void HandleButtonUp();

    virtual void HandleCheckedChanged(bool checked);

    virtual void OnStateChanged(VisualState state);

    void SetState(VisualState state);

private:
    void PositionLabel();

private:
    std::string mText;

    std::map<unsigned int, std::function<void()>> mOnClick;
    std::map<unsigned int, std::function<void(bool)>> mOnToggle;

    graphic::Font * mFontLabel = nullptr;

    // actual objects created by SetBackground and SetLabel
    graphic::Renderable * mBg = nullptr;
    graphic::Renderable * mLabel = nullptr;

    // pointers to the current active objects
    graphic::Renderable * mCurrBg = nullptr;
    graphic::Renderable * mCurrLabel = nullptr;

    VisualState mState = NULL_STATE;

    bool mCheckable = false;
    bool mChecked = false;
    bool mExclusive = false;
};

inline bool PushButton::IsCheckable() const { return mCheckable; }
inline void PushButton::SetCheckable(bool val)
{
    mCheckable = val;
    mChecked = false;
}
inline bool PushButton::IsChecked() const { return mChecked; }

inline bool PushButton::IsExclusive() const { return mExclusive; }
inline void PushButton::SetExclusive(bool val) { mExclusive = val; }

inline const std::string & PushButton::GetText() const { return mText; }

inline PushButton::VisualState PushButton::GetState() const { return mState; }

} // namespace sgui
} // namespace sgl