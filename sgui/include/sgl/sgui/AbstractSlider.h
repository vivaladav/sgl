#pragma once

#include "sgl/sgui/Widget.h"

#include <functional>

namespace sgl
{

namespace sgui
{

class AbstractSlider : public Widget
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
    AbstractSlider(Orientation o, Widget * parent);

    Orientation GetOrientation() const;
    VisualState GetState() const;

    void SetMinMax(int min, int max);
    int GetValue() const;
    int GetValuePerc() const;
    void SetValue(int val);

    void SetStep(int val);

    void SetOnValueChanged(const std::function<void(int)> & f);

    bool IsScreenPointInside(int x, int y) override;

protected:
    void HandleMouseButtonDown(core::MouseButtonEvent & event) override;
    void HandleMouseButtonUp(core::MouseButtonEvent & event) override;
    void HandleMouseMotion(core::MouseMotionEvent & event) override;
    void HandleMouseOut() override;
    void HandleMousePositionX(int x);
    void HandleMousePositionY(int y);
    void HandleMousePosition(int pos, int pos0, int pos1);

    virtual void OnStateChanged(VisualState state);

    virtual void HandleValueChanged(int val);

    int GetBarFullWidth() const;
    int GetBarFullHeight() const;
    void SetSlidingAreaSize(int w, int h);
    void SetSlidingAreaPosition(int x, int y);

private:
    std::function<void(int)> mOnValChanged;

    Orientation mOrientation;

    VisualState mState = NORMAL;

    int mSlidingAreaX = 0;
    int mSlidingAreaY = 0;
    int mSlidingAreaW = 0;
    int mSlidingAreaH = 0;

    int mMin = 0;
    int mMax = 100;
    int mValue = 0;
    int mValuePerc = 0;
    int mStep = 1;

    bool mDragging = false;
};

inline AbstractSlider::Orientation AbstractSlider::GetOrientation() const { return mOrientation;  }
inline AbstractSlider::VisualState AbstractSlider::GetState() const { return mState; }

inline int AbstractSlider::GetValue() const { return mValue; }
inline int AbstractSlider::GetValuePerc() const { return mValuePerc; }

inline void AbstractSlider::SetStep(int val) { mStep = val; }

inline void AbstractSlider::SetOnValueChanged(const std::function<void(int)> & f) { mOnValChanged = f; }

inline int AbstractSlider::GetBarFullWidth() const { return mSlidingAreaW; }
inline int AbstractSlider::GetBarFullHeight() const { return mSlidingAreaH; }
inline void AbstractSlider::SetSlidingAreaSize(int w, int h)
{
    mSlidingAreaW = w;
    mSlidingAreaH = h;
}
inline void AbstractSlider::SetSlidingAreaPosition(int x, int y)
{
    mSlidingAreaX = x;
    mSlidingAreaY = y;
}

} // namespace sgui
} // namespace sgl
