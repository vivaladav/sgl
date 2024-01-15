#pragma once

#include "sgl/sgui/Widget.h"

#include <functional>
#include <map>

namespace sgl
{

namespace sgui
{

class AbstractButton : public Widget
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
    AbstractButton(Widget * parent = nullptr);

    int GetShortcutKey() const;
    void SetShortcutKey(int key);

    VisualState GetState() const;

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

protected:
    void HandleStateEnabled() override;
    void HandleStateDisabled() override;

    void HandleMouseButtonDown(sgl::core::MouseButtonEvent & event) override;
    void HandleMouseButtonUp(sgl::core::MouseButtonEvent & event) override;
    void HandleMouseOver() override;
    void HandleMouseOut() override;

    void HandleKeyDown(sgl::core::KeyboardEvent & event) override;
    void HandleKeyUp(sgl::core::KeyboardEvent & event) override;

    virtual void HandleButtonDown();
    virtual void HandleButtonUp();

    virtual void HandleCheckedChanged(bool checked);

    virtual void OnStateChanged(VisualState state);

    void InitState(VisualState state);
    void SetState(VisualState state);

private:
    std::map<unsigned int, std::function<void()>> mOnClick;
    std::map<unsigned int, std::function<void(bool)>> mOnToggle;

    VisualState mState = NULL_STATE;

    int mShortcutKey = -1;

    bool mCheckable = false;
    bool mChecked = false;
    bool mExclusive = false;
};

inline int AbstractButton::GetShortcutKey() const { return mShortcutKey; }
inline void AbstractButton::SetShortcutKey(int key) { mShortcutKey = key; }

inline AbstractButton::VisualState AbstractButton::GetState() const { return mState; }

inline bool AbstractButton::IsCheckable() const { return mCheckable; }
inline void AbstractButton::SetCheckable(bool val)
{
    mCheckable = val;
    mChecked = false;
}
inline bool AbstractButton::IsChecked() const { return mChecked; }

inline bool AbstractButton::IsExclusive() const { return mExclusive; }
inline void AbstractButton::SetExclusive(bool val) { mExclusive = val; }

inline void AbstractButton::InitState(VisualState state) { mState = state; }

} // namespace sgui
} // namespace sgl
