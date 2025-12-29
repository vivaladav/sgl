#include "sgl/sgui/WidgetContainer.h"

#include "sgl/core/event/KeyboardEvent.h"
#include "sgl/core/event/MouseButtonEvent.h"
#include "sgl/core/event/MouseMotionEvent.h"
#include "sgl/core/event/MouseWheelEvent.h"
#include "sgl/graphic/Renderer.h"
#include "sgl/sgui/Stage.h"
#include "sgl/sgui/Widget.h"
#include "sgl/sgui/event/VisibilityChangeEvent.h"

#include <algorithm>

namespace sgl
{
namespace sgui
{

WidgetContainer::~WidgetContainer()
{
    ClearWidgets();
}

void WidgetContainer::ClearWidgets()
{
    auto it = mWidgets.begin();

    while(!mWidgets.empty())
    {
        Widget * w = *it;

        it = mWidgets.erase(it);

        // delete Widget after erase because destructor will call RemoveChild
        delete w;
    }
}

void WidgetContainer::MoveChildToBack(Widget * w)
{
    auto res = std::find(mWidgets.begin(), mWidgets.end(), w);

    // remove widget from children
    if(mWidgets.end() == res)
        return ;

    mWidgets.erase(res);

    // add widget to front of list which is back of screen
    mWidgets.emplace_front(w);
}

void WidgetContainer::MoveChildToFront(Widget * w)
{
    auto res = std::find(mWidgets.begin(), mWidgets.end(), w);

    // remove widget from children
    if(mWidgets.end() == res)
        return ;

    mWidgets.erase(res);

    // add widget to back of list which is front of screen
    mWidgets.emplace_back(w);
}

void WidgetContainer::ClearFocus()
{
    // update flag and propagate
    mFocus = false;

    for(Widget * w : mWidgets)
        w->ClearFocus();
}

void WidgetContainer::SetFocus()
{
    // first clear focus for all widgets
    auto stage = Stage::Instance();
    stage->ClearFocus();

    // update flag and propagate
    mFocus = true;

    for(Widget * w : mWidgets)
        w->PropagateFocus();
}

void WidgetContainer::SetVisible(bool val)
{
    if(val == mVisible)
        return ;

    mVisible = val;

    // handle visibility changed
    VisibilityChangeEvent e(val);
    HandleVisibilityChanged(e);
    PropagateVisibilityChanged(e);
}

void WidgetContainer::AddChild(Widget * w)
{
    auto it = std::find(mWidgets.begin(), mWidgets.end(), w);

    if(it == mWidgets.end())
        mWidgets.emplace_back(w);
}

void WidgetContainer::RemoveChild(Widget * w)
{
    auto it = std::find(mWidgets.begin(), mWidgets.end(), w);

    if(it != mWidgets.end())
        mWidgets.erase(it);
}

void WidgetContainer::HandleChildEnableChanged(Widget * /*child*/)
{
    // TODO - handle enable changed in child
}

void WidgetContainer::HandleChildVisibleChanged(Widget * /*child*/)
{
    // TODO - handle visible changed in child
}

void WidgetContainer::PropagateMouseButtonDown(core::MouseButtonEvent & event)
{
    const int x = event.GetX();
    const int y = event.GetY();

    for(auto it = mWidgets.rbegin(); it != mWidgets.rend(); ++it)
    {
        Widget * w = *it;

        if(w->IsEnabled() && w->IsVisible()) // TODO remove this when implemented rendering and active lists
        {
            if(w->IsScreenPointInside(x, y))
            {
                w->PropagateMouseButtonDown(event);

                // stop propagation if event is consumed
                if(event.IsConsumed())
                    break;

                w->HandleMouseButtonDown(event);
            }
        }
    }
}

void WidgetContainer::PropagateMouseButtonUp(core::MouseButtonEvent & event)
{
    const int x = event.GetX();
    const int y = event.GetY();

    for(auto it = mWidgets.rbegin(); it != mWidgets.rend(); ++it)
    {
        Widget * w = *it;

        if(w->IsEnabled() && w->IsVisible()) // TODO remove this when implemented rendering and active lists
        {
            if(w->IsScreenPointInside(x, y))
            {
                w->PropagateMouseButtonUp(event);

                // stop propagation if event is consumed
                if(event.IsConsumed())
                    break;

                w->HandleMouseButtonUp(event);
            }
        }
    }
}

void WidgetContainer::PropagateMouseMotion(core::MouseMotionEvent & event)
{
    const int x = event.GetX();
    const int y = event.GetY();

    for(auto it = mWidgets.rbegin(); it != mWidgets.rend(); ++it)
    {
        Widget * w = *it;

        if(w->IsEnabled() && w->IsVisible()) // TODO remove this when implemented rendering and active lists
        {
            if(w->IsScreenPointInside(x, y))
            {
                w->PropagateMouseMotion(event);

                // stop propagation if event is consumed
                if(event.IsConsumed())
                    break;

                w->SetMouseOver();

                w->HandleMouseMotion(event);
            }
            else
                w->SetMouseOut();
        }
    }
}

void WidgetContainer::PropagateMouseWheel(core::MouseWheelEvent & event)
{
    for(auto it = mWidgets.rbegin(); it != mWidgets.rend(); ++it)
    {
        Widget * w = *it;

        if(w->IsEnabled() && w->IsVisible()) // TODO remove this when implemented rendering and active lists
        {
            w->PropagateMouseWheel(event);

            // stop propagation if event is consumed
            if(event.IsConsumed())
                break;

            if(w->HasFocus())
                w->HandleMouseWheel(event);
        }
    }
}

void WidgetContainer::PropagateKeyDown(core::KeyboardEvent & event)
{
    for(auto it = mWidgets.rbegin(); it != mWidgets.rend(); ++it)
    {
        Widget * w = *it;

        if(w->IsEnabled() && w->IsVisible()) // TODO remove this when implemented rendering and active lists
        {
            w->PropagateKeyDown(event);

            // stop propagation if event is consumed
            if(event.IsConsumed())
                break;

            if(w->HasFocus())
                w->HandleKeyDown(event);
        }
    }
}

void WidgetContainer::PropagateKeyUp(core::KeyboardEvent & event)
{
    for(auto it = mWidgets.rbegin(); it != mWidgets.rend(); ++it)
    {
        Widget * w = *it;

        if(w->IsEnabled() && w->IsVisible()) // TODO remove this when implemented rendering and active lists
        {
            w->PropagateKeyUp(event);

            // stop propagation if event is consumed
            if(event.IsConsumed())
                break;

            if(w->HasFocus())
                w->HandleKeyUp(event);
        }
    }
}

void WidgetContainer::HandleVisibilityChanged(VisibilityChangeEvent & event)
{
}

void WidgetContainer::PropagateVisibilityChanged(VisibilityChangeEvent & event)
{
    for(Widget * w : mWidgets)
    {
        if(!event.IsVisible() && w->IsShowingTooltip())
            w->HideTooltip();

        w->HandleVisibilityChanged(event);
        w->PropagateVisibilityChanged(event);
    }
}

void WidgetContainer::PropagateRender()
{
    for(Widget * w : mWidgets)
    {
        if(w->IsVisible() && w->IsInVisibleArea())  // TODO remove this when implemented rendering lists
        {
            if(w->mVisibleAreaSet)
            {
                auto renderer = sgl::graphic::Renderer::Instance();

                renderer->SetClipping(w->mVisX1, w->mVisY1, w->mVisW, w->mVisH);
                w->OnRender();
                w->PropagateRender();
                renderer->ClearClipping();
            }
            else
            {
                w->OnRender();
                w->PropagateRender();
            }
        }
    }
}

void WidgetContainer::PropagateFocus()
{
    mFocus = true;

    for(Widget * w : mWidgets)
        w->PropagateFocus();
}

void WidgetContainer::PropagateUpdate(float delta)
{
    for(Widget * w : mWidgets)
    {
        // do not update if disabled
        if(!w->IsEnabled())
            continue ;

        if(w->IsMouseOver())
            w->UpdateTimeOver();

        w->OnUpdate(delta);
        w->PropagateUpdate(delta);
    }
}

} // namespace sgui
} // namespace sgl
