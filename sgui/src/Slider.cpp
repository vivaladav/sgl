#include "sgl/sgui/Slider.h"

#include "sgl/core/event/MouseButtonEvent.h"
#include "sgl/core/event/MouseMotionEvent.h"
#include "sgl/graphic/Image.h"

#include <cmath>

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

void Slider::SetMinMax(int min, int max)
{
    mMin = min;
    mMax = max;

    if(mValue < mMin)
        mValue = mMin;
    else if(mValue > mMax)
        mValue = mMax;
    else
        return ;

    HandleValueChanged(mValue);
    mOnValChanged(mValue);
}

void Slider::SetValue(int val)
{
    if(mValue == val)
        return ;

    mValue = val;

    mValuePerc = (mValue - mMin) * 100 / (mMax - mMin);

    HandleValueChanged(val);
    mOnValChanged(val);
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
        HandleMousePositionX(event.GetX());
    // VERTICAL SLIDER
    else
        HandleMousePositionY(event.GetY());

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
         HandleMousePositionX(event.GetX());
    // VERTICAL SLIDER
    else
        HandleMousePositionY(event.GetY());
}

void Slider::HandleMouseOut()
{
    mDragging = false;
}

void Slider::HandleMousePositionX(int x)
{
    const int barX0 = mBar->GetX();
    const int barX1 = barX0 + mBarWidth;

    HandleMousePosition(x, barX0, barX1);
}

void Slider::HandleMousePositionY(int y)
{
    const int barY0 = mBar->GetY();
    const int barY1 = barY0 + mBarHeight;

    HandleMousePosition(y, barY0, barY1);
}

void Slider::HandleMousePosition(int pos, int pos0, int pos1)
{
    const float segments = static_cast<float>(mMax - mMin) / static_cast<float>(mStep);
    const float segmentSizePerc = 100.f / segments;

    float perc = 0.f;

    if(pos <= pos0)
        perc = 0.f;
    else if(pos >= pos1)
        perc = 100.f;
    else
        perc = 100.f * (pos - pos0) / static_cast<float>(mBarWidth);

    const int segmentInd = static_cast<int>(std::roundf(perc / segmentSizePerc));

    mValuePerc = segmentInd * segmentSizePerc;

    const int val = mMin + segmentInd * mStep;

    if(mValue != val)
    {
        mValue = val;

        HandleValueChanged(val);
        mOnValChanged(val);
    }
}

void Slider::OnStateChanged(VisualState) { }

void Slider::HandleValueChanged(int) {  }

} // namespace sgui
} // namespace sgl
