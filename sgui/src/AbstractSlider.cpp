#include "sgl/sgui/AbstractSlider.h"

#include "sgl/core/event/MouseButtonEvent.h"
#include "sgl/core/event/MouseMotionEvent.h"

#include <cmath>

namespace sgl
{
namespace sgui
{

AbstractSlider::AbstractSlider(Orientation o, Widget * parent)
    : Widget(parent)
    , mOnValChanged([](int){})
    , mOrientation(o)
{
}

void AbstractSlider::SetMinMax(int min, int max)
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

void AbstractSlider::SetValue(int val)
{
    if(val < mMin)
        val = mMin;
    else if(val > mMax)
        val = mMax;

    if(mValue == val)
        return ;

    mValue = val;

    mValuePerc = (mValue - mMin) * 100 / (mMax - mMin);

    HandleValueChanged(val);
    mOnValChanged(val);
}

bool AbstractSlider::IsScreenPointInside(int x, int y)
{
    // always inside while dragging so to allow control anywhere the mouse is
    return mDragging || Widget::IsScreenPointInside(x, y);
}

void AbstractSlider::HandleMouseButtonDown(core::MouseButtonEvent & event)
{
    // only handle left button
    if(event.GetButton() != core::MouseButtonEvent::BUTTON_LEFT)
        return ;

    // start dragging
    mDragging = true;

    // HORIZONTAL AbstractSlider
    if(HORIZONTAL == mOrientation)
        HandleMousePositionX(event.GetX());
    // VERTICAL AbstractSlider
    else
        HandleMousePositionY(event.GetY());

    event.SetConsumed();
}

void AbstractSlider::HandleMouseButtonUp(core::MouseButtonEvent & event)
{
    mDragging = false;
}

void AbstractSlider::HandleMouseMotion(core::MouseMotionEvent & event)
{
    if(!mDragging)
        return ;

    // HORIZONTAL AbstractSlider
    if(HORIZONTAL == mOrientation)
         HandleMousePositionX(event.GetX());
    // VERTICAL AbstractSlider
    else
        HandleMousePositionY(event.GetY());
}

void AbstractSlider::HandleMouseOut()
{
    mDragging = false;
}


void AbstractSlider::HandleMousePositionX(int x)
{
    const int barX0 = mSlidingAreaX;
    const int barX1 = barX0 + GetSlidingAreaWidth();
    HandleMousePosition(x, barX0, barX1);
}

void AbstractSlider::HandleMousePositionY(int y)
{
    const int barY0 = mSlidingAreaY;
    const int barY1 = barY0 + GetSlidingAreaHeight();
    HandleMousePosition(y, barY0, barY1);
}

void AbstractSlider::HandleMousePosition(int pos, int pos0, int pos1)
{
    const float segments = static_cast<float>(mMax - mMin) / static_cast<float>(mStep);
    const float segmentSizePerc = 100.f / segments;

    float perc = 0.f;

    if(pos <= pos0)
        perc = 0.f;
    else if(pos >= pos1)
        perc = 100.f;
    else
    {
        const float side = (HORIZONTAL == mOrientation) ? mSlidingAreaW : mSlidingAreaH;
        perc = 100.f * (pos - pos0) / side;
    }

    const int segmentInd = static_cast<int>(std::roundf(perc / segmentSizePerc));
    const int val = mMin + segmentInd * mStep;

     mValuePerc = static_cast<int>(std::roundf(segmentInd * segmentSizePerc));

    if(mValue != val)
    {
        mValue = val;

        HandleValueChanged(val);
        mOnValChanged(val);
    }
}

void AbstractSlider::OnStateChanged(VisualState) { }

void AbstractSlider::HandleValueChanged(int) {  }

} // namespace sgui
} // namespace sgl
