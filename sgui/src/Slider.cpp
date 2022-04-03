#include "sgl/sgui/Slider.h"

#include "sgl/core/event/MouseButtonEvent.h"
#include "sgl/core/event/MouseMotionEvent.h"
#include "sgl/graphic/Image.h"

#include <iostream>

namespace sgl
{
namespace sgui
{

Slider::Slider(Orientation o, Widget * parent)
    : Widget(parent)
    , mOnValChanged([](int){})
    , mOrientation(o)
{
    mBg = new graphic::Image;
    RegisterRenderable(mBg);

    mBar = new graphic::Image;
    RegisterRenderable(mBar);

    mButton = new graphic::Image;
    RegisterRenderable(mButton);
}

bool Slider::IsScreenPointInside(int x, int y)
{
    // always inside while dragging so to allow control anywhere the mouse is
    return mDragging || Widget::IsScreenPointInside(x, y);
}

void Slider::HandleMouseButtonDown(core::MouseButtonEvent & event)
{
    // only handle left button
    if(event.GetButton() != core::MouseButtonEvent::BUTTON_LEFT)
        return ;

    // start dragging
    mDragging = true;

    // HORIZONTAL SLIDER
    if(HORIZONTAL == mOrientation)
    {
        const int x = event.GetX();

        const int barX0 = mBar->GetX();
        const int barX1 = barX0 + mBarWidth;

        int val = -1;

        if(x <= barX0)
            val = 0;
        else if(x >= barX1)
            val = 100;
        else
            val = 100 * (x - barX0) / mBarWidth;

        if(mValue != val)
        {
            mValue = val;

            HandleValueChanged(val);
            mOnValChanged(val);
        }
    }
    // VERTICAL SLIDER
    else
    {

    }

    event.SetConsumed();
}

void Slider::HandleMouseButtonUp(core::MouseButtonEvent & event)
{
    mDragging = false;
}

void Slider::HandleMouseMotion(core::MouseMotionEvent & event)
{
    if(!mDragging)
        return ;

    // HORIZONTAL SLIDER
    if(HORIZONTAL == mOrientation)
    {
        const int x = event.GetX();

        const int barX0 = mBar->GetX();
        const int barX1 = barX0 + mBarWidth;

        int val = -1;

        if(x <= barX0)
            val = 0;
        else if(x >= barX1)
            val = 100;
        else
            val = 100 * (x - barX0) / mBarWidth;

        if(mValue != val)
        {
            mValue = val;

            HandleValueChanged(val);
            mOnValChanged(val);
        }
    }
    // VERTICAL SLIDER
    else
    {

    }
}

void Slider::HandleMouseOut()
{
    mDragging = false;
}

void Slider::OnStateChanged(VisualState) { }

void Slider::HandleValueChanged(int) {  }

} // namespace sgui
} // namespace sgl
