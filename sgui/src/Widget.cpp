#include "sgl/sgui/Widget.h"

#include "sgl/core/event/MouseButtonEvent.h"
#include "sgl/core/event/MouseMotionEvent.h"
#include "sgl/core/event/MouseWheelEvent.h"
#include "sgl/graphic/Camera.h"
#include "sgl/graphic/Renderable.h"
#include "sgl/graphic/Renderer.h"
#include "sgl/sgui/Stage.h"

#include <algorithm>

#include <cmath>

namespace sgl
{
namespace sgui
{

Widget::Widget(Widget * parent)
    : mCamera(graphic::Camera::GetDummyCamera())
{
    SetParent(parent);

    static unsigned int ids = 0;
    mId = ++ids;
}

Widget::~Widget()
{
    auto stage = Stage::Instance();

    // remove itself from parent
    if(mParent)
        mParent->RemoveChild(this);
    else
        stage->RemoveChild(this);

    // delete renderables
    for(auto elem : mRenderables)
        delete elem;

    // clear focus
    if(HasFocus())
    {
        ClearFocus();
        stage->SetFocus();
    }

    stage->CancelDeleteLater(this);
}

void Widget::SetParent(Widget * parent)
{
    // remove from current parent
    if(mParent)
    {
        mParent->RemoveChild(this);
        mParent->UpdateSize();
        mParent = nullptr;
    }
    else if(mStage)
    {
        mStage->RemoveChild(this);
        mStage = nullptr;
    }

    // set new parent
    if(parent)
    {
        mParent = parent;
        parent->AddChild(this);
        parent->UpdateSize();

        const int dx = parent->GetScreenX();
        const int dy = parent->GetScreenY();
        SetScreenPosition(mRelX + dx, mRelY + dy);
        PropagateParentPositionChanged(dx, dy);
    }
    else
    {
        mStage = Stage::Instance();
        mStage->AddChild(this);

        const int dx = mRelX - mScreenX;
        const int dy = mRelY - mScreenY;
        SetScreenPosition(mRelX, mRelY);
        PropagateParentPositionChanged(dx, dy);
    }
}

void Widget::SetTooltip(Widget * t)
{
    mTooltip = t;

    if(mTooltip != nullptr)
    {
        mTooltip->SetParent(nullptr);
        mTooltip->SetVisible(false);
    }
}

void Widget::SetEnabled(bool val)
{
    if(val == mEnabled)
        return ;

    mEnabled = val;

    if(val)
        HandleStateEnabled();
    else
        HandleStateDisabled();

    if(mParent)
        mParent->HandleChildEnableChanged(this);
    else
        mStage->HandleChildEnableChanged(this);
}

void Widget::SetVisible(bool val)
{
    if(val == IsVisible())
        return ;

    WidgetContainer::SetVisible(val);

    if(!val)
        ClearFocus();

    // notify parent of visibility change
    if(mParent)
    {
        mParent->HandleChildVisibleChanged(this);
        // TODO this should be in HandleChildVisibleChanged when implemented
        mParent->UpdateSize();
    }
    else
        mStage->HandleChildVisibleChanged(this);
}

void Widget::SetAlpha(unsigned char alpha)
{
    // nothing changed -> exit
    if(alpha == mA)
        return ;

    mA = alpha;

    // update graphic elements
    for(auto elem : mRenderables)
        elem->SetAlpha(alpha);

    // propagate to sub-widgets
    for(Widget * w : mWidgets)
        w->SetAlpha(alpha);
}

void Widget::SetCamera(graphic::Camera * cam)
{
    // same camera -> exit
    if(cam == mCamera)
        return ;

    mCamera = cam;

    // update graphic elements
    for(auto elem : mRenderables)
        elem->SetCamera(mCamera);
}

void Widget::DeleteLater()
{
    Stage::Instance()->DeleteLater(this);
}

void Widget::Refresh() {}

void Widget::SetSize(int w, int h)
{
    mWidth = w;
    mHeight = h;

    if(mParent)
        mParent->UpdateSize();
}

void Widget::HandleMouseOver() { }

void Widget::HandleMouseOut() { }

void Widget::RegisterRenderable(graphic::Renderable * elem)
{
    // check element not added already
    auto it = std::find(mRenderables.begin(), mRenderables.end(), elem);

    if(it != mRenderables.end())
        return ;

    // add element
    mRenderables.push_back(elem);

    elem->SetCamera(mCamera);
}

void Widget::UnregisterRenderable(graphic::Renderable * elem)
{
    auto it = std::find(mRenderables.begin(), mRenderables.end(), elem);

    if(it != mRenderables.end())
        mRenderables.erase(it);
}

void Widget::ShowTooltip()
{
    mOnShowingTooltip();

    // position tooltip
    const auto renderer = graphic::Renderer::Instance();
    const int screenW = renderer->GetWidth();
    const int screenH = renderer->GetHeight();
    const int tooltipW = mTooltip->GetWidth();
    const int tooltipH = mTooltip->GetHeight();
    const int mouseX = Stage::Instance()->GetMouseX();
    const int mouseY = Stage::Instance()->GetMouseY();

    int x = mouseX + mTooltipMarginHoriz;

    if(x + tooltipW > screenW)
    {
        x = mouseX - mTooltipMarginHoriz - tooltipW;

        if(x < 0)
            x = 0;
    }

    int y = mouseY + mTooltipMarginVert;

    if(y + tooltipH > screenH)
    {
        y = mouseY - mTooltipMarginVert - tooltipH;

        if(y < 0)
            y = 0;
    }

    mTooltip->SetPosition(x, y);

    // make it visible
    mTooltip->SetVisible(true);
    Stage::Instance()->MoveChildToFront(mTooltip);

    mTooltipShowing = true;
    mTooltipShowed = true;
}

void Widget::HideTooltip()
{
    mTooltip->SetVisible(false);

    mTooltipShowing = false;
}

// current behavior for Widgets is to grow according to children position and size
void Widget::UpdateSize()
{
    // resize not allowed with FIXED policy
    if(FIXED == mResizePol)
        return ;

    // TODO decide what to do with negative position
    int maxX = 0;
    int maxY = 0;

    for(Widget * w : mWidgets)
    {
        // skip invisible widgets
        if(!w->IsVisible())
            continue;

        int x = w->GetX() + w->GetWidth();
        int y = w->GetY() + w->GetHeight();

        if(x > maxX)
            maxX = x;

        if(y > maxY)
            maxY = y;
    }

    // update size if different than current
    if(GROW_ONLY == mResizePol)
    {
        if(maxX > mWidth)
            mWidth = maxX;

        if(maxY > mHeight)
            mHeight = maxY;
    }
    else
    {
        if(maxX != mWidth)
            mWidth = maxX;

        if(maxY != mHeight)
            mHeight = maxY;
    }
}

void Widget::SetPosition(int x, int y)
{
    const int dx = x - mRelX;
    const int dy = y - mRelY;

    mRelX = x;
    mRelY = y;

    SetScreenPosition(mScreenX + dx, mScreenY + dy);

    PropagateParentPositionChanged(dx, dy);

    if(mParent)
        mParent->UpdateSize();
}

void Widget::SetX(int x)
{
    const int dx = x - mRelX;

    mRelX = x;

    SetScreenPosition(mScreenX + dx, mScreenY);

    PropagateParentPositionChanged(dx, 0);

    if(mParent)
        mParent->UpdateSize();
}

void Widget::SetY(int y)
{
    const int dy = y - mRelY;

    mRelY = y;

    SetScreenPosition(mScreenX, mScreenY + dy);

    PropagateParentPositionChanged(0, dy);

    if(mParent)
        mParent->UpdateSize();
}

bool Widget::IsScreenPointInside(int x, int y)
{
    // check children widgets first in case there's some special case (like Slider)
    for(Widget * w : mWidgets)
    {
        if(w->IsScreenPointInside(x, y))
            return true;
    }

    return x > mScreenX && x < (mScreenX + mWidth) && y > mScreenY && y < (mScreenY + mHeight);
}

void Widget::HandlePositionChanged() { }

void Widget::OnRender()
{
    for(auto elem : mRenderables)
        elem->Render();
}

void Widget::OnUpdate(float delta) { }

void Widget::UpdateTimeOver()
{
    const auto t1 = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<float> durationOver = t1 - mTOver0;
    const float sec2ms = 1000.f;
    mTimeOverMs = static_cast<int>(std::roundf(sec2ms * durationOver.count()));

    if(nullptr == mTooltip)
        return ;

    if(!mTooltip->IsVisible())
    {
        if(!mTooltipShowed && IsVisibleOnScreen() && GetTimerOver() >= mTooltipTimeDelayMs)
            ShowTooltip();
    }
    else
    {
        if(GetTimerOver() >= mTooltipTimeDelayMs + mTooltipTimeShowingMs)
            HideTooltip();
    }
}

void Widget::SetScreenPosition(int x, int y)
{
    mScreenX = x;
    mScreenY = y;

    if(mVisibleAreaSet)
        UpdateVisibleAreaPoints();

    HandlePositionChanged();
}

void Widget::HandleStateEnabled() { }
void Widget::HandleStateDisabled() { }

void Widget::HandleMouseButtonDown(core::MouseButtonEvent &) { }
void Widget::HandleMouseButtonUp(core::MouseButtonEvent &) { }
void Widget::HandleMouseMotion(core::MouseMotionEvent &) { }
void Widget::HandleMouseWheel(core::MouseWheelEvent &) { }

void Widget::HandleKeyDown(core::KeyboardEvent &) { }
void Widget::HandleKeyUp(core::KeyboardEvent &) { }

void Widget::SetMouseOver()
{
    // mouse already over -> nothing to do
    if(mMouseOver)
        return;

    mMouseOver = true;

    mTOver0 = std::chrono::high_resolution_clock::now();

    HandleMouseOver();
}

void Widget::SetMouseOut()
{
    // mouse already over -> nothing to do
    if(!mMouseOver)
        return;

    mMouseOver = false;

    // propagate out to handle case of overlapping widgets
    for(Widget * w : mWidgets)
        w->SetMouseOut();

    if(mTooltip)
    {
        HideTooltip();
        // clear showed flag
        mTooltipShowed = false;
    }

    HandleMouseOut();
}

void Widget::HandleParentPositionChanged(int dx, int dy)
{
    SetScreenPosition(mScreenX + dx, mScreenY + dy);
}

void Widget::PropagateParentPositionChanged(int dx, int dy)
{
    for(Widget * w : mWidgets)
    {
        w->HandleParentPositionChanged(dx, dy);
        w->PropagateParentPositionChanged(dx, dy);
    }
}

bool Widget::IsVisibleOnScreen() const
{
    return IsVisible() && IsInVisibleArea() &&
           (nullptr == mParent || mParent->IsVisibleOnScreen());
}

} // namespace sgui
} // namespace sgl
