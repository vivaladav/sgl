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

    void SetMinMax(int min, int max);
    int GetValue() const;
    int GetValuePerc() const;

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
    void SetBarFullSize(int w, int h);

protected:
    graphic::Image * mBg = nullptr;
    graphic::Image * mBar = nullptr;
    graphic::Image * mButton = nullptr;

private:
    std::function<void(int)> mOnValChanged;

    Orientation mOrientation;

    VisualState mState = NORMAL;

    int mBarWidth = 0;
    int mBarHeight = 0;

    int mMin = 0;
    int mMax = 100;
    int mValue = 0;
    int mValuePerc = 0;
    int mStep = 1;

    bool mDragging = false;
};

inline Slider::Orientation Slider::GetOrientation() const { return mOrientation;  }
inline Slider::VisualState Slider::GetState() const { return mState; }

inline int Slider::GetValue() const { return mValue; }
inline int Slider::GetValuePerc() const { return mValuePerc; }

inline void Slider::SetStep(int val) { mStep = val; }

inline void Slider::SetOnValueChanged(const std::function<void(int)> & f) { mOnValChanged = f; }

inline int Slider::GetBarFullWidth() const { return mBarWidth; }
inline int Slider::GetBarFullHeight() const { return mBarHeight; }
inline void Slider::SetBarFullSize(int w, int h)
{
    mBarWidth = w;
    mBarHeight = h;
}

} // namespace sgui
} // namespace sgl
