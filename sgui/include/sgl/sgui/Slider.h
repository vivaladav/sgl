#pragma once

#include "sgl/sgui/Widget.h"

#include <functional>

namespace sgl
{

namespace graphic
{
    class Image;
    class Texture;
}

namespace sgui
{

class Slider : public Widget
{
public:
    enum Orientation
    {
        HORIZONTAL,
        VERTICAL
    };

    enum VisualState : int
    {
        NORMAL = 0,
        DISABLED,
        MOUSE_OVER,
        DRAGGING,

        NUM_VISUAL_STATES,

        NULL_STATE
    };

public:
    Slider(Orientation o, Widget * parent);

    Orientation GetOrientation() const;
    VisualState GetState() const;

    int GetValue() const;

    void SetOnValueChanged(const std::function<void(int)> & f);

    bool IsScreenPointInside(int x, int y) override;

protected:
    void HandleMouseButtonDown(core::MouseButtonEvent & event) override;
    void HandleMouseButtonUp(core::MouseButtonEvent & event) override;
    void HandleMouseMotion(core::MouseMotionEvent & event) override;
    void HandleMouseOut() override;

    virtual void OnStateChanged(VisualState state);

    virtual void HandleValueChanged(int val);

    int GetBarFullWidth() const;
    void SetBarFullWidth(int val);

protected:
    graphic::Image * mBg = nullptr;
    graphic::Image * mBar = nullptr;
    graphic::Image * mButton = nullptr;

private:
    std::function<void(int)> mOnValChanged;

    Orientation mOrientation;

    VisualState mState = NORMAL;

    int mBarWidth = 0;

    int mMin = 0;
    int mMax = 100;
    int mValue = 0;
    int mStep = 1;

    bool mDragging = false;
};

inline Slider::Orientation Slider::GetOrientation() const { return mOrientation;  }
inline Slider::VisualState Slider::GetState() const { return mState; }

inline int Slider::GetValue() const { return mValue; }

inline void Slider::SetOnValueChanged(const std::function<void(int)> & f) { mOnValChanged = f; }

inline int Slider::GetBarFullWidth() const { return mBarWidth; }
inline void Slider::SetBarFullWidth(int val) { mBarWidth = val; }

} // namespace sgui
} // namespace sgl
