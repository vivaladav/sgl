#pragma once

#include "sgl/sgui/Widget.h"

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

protected:
    void HandleMouseButtonDown(core::MouseButtonEvent & event) override;
    void HandleMouseButtonUp(core::MouseButtonEvent & event) override;
    void HandleMouseMotion(core::MouseMotionEvent & event) override;

    virtual void OnStateChanged(VisualState state);

protected:
    graphic::Image * mBg = nullptr;
    graphic::Image * mBar = nullptr;
    graphic::Image * mButton = nullptr;

private:
    Orientation mOrientation;

    bool mDragging = false;

    VisualState mState = NORMAL;
};

inline Slider::Orientation Slider::GetOrientation() const { return mOrientation;  }
inline Slider::VisualState Slider::GetState() const { return mState; }

} // namespace sgui
} // namespace sgl
