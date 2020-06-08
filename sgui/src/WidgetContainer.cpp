#include "sgui/WidgetContainer.h"

#include "core/event/MouseButtonEvent.h"
#include "core/event/MouseMotionEvent.h"
#include "sgui/Widget.h"

#include <algorithm>

namespace lib
{
namespace sgui
{

WidgetContainer::~WidgetContainer()
{
    for(Widget * w : mWidgets)
        delete w;
}

void WidgetContainer::AddChild(Widget * w)
{
    mWidgets.emplace_back(w);
}

void WidgetContainer::RemoveChild(Widget * w)
{
    auto res = std::find(mWidgets.begin(), mWidgets.end(), w);

    mWidgets.erase(res);
}

void WidgetContainer::OnChildEnableChanged(Widget * /*child*/)
{
    // TODO - handle enable changed in child
}

void WidgetContainer::OnChildVisibleChanged(Widget * /*child*/)
{
    // TODO - handle visible changed in child
}

void WidgetContainer::PropagateMouseButtonDown(const core::MouseButtonEvent & event)
{
    const int x = event.GetX();
    const int y = event.GetY();

    for(Widget * w : mWidgets)
    {
        if(w->IsScreenPointInside(x, y))
        {
            w->PropagateMouseButtonDown(event);
            w->HandleMouseButtonDown(event);
        }
    }
}

void WidgetContainer::PropagateMouseButtonUp(const core::MouseButtonEvent & event)
{
    const int x = event.GetX();
    const int y = event.GetY();

    for(Widget * w : mWidgets)
    {
        if(w->IsScreenPointInside(x, y))
        {
            w->PropagateMouseButtonUp(event);
            w->HandleMouseButtonUp(event);
        }
    }
}

void WidgetContainer::PropagateMouseMotion(const core::MouseMotionEvent & event)
{
    const int x = event.GetX();
    const int y = event.GetY();

    for(Widget * w : mWidgets)
    {
        if(w->IsScreenPointInside(x, y))
        {
            w->PropagateMouseMotion(event);

            w->SetMouseOver();

            w->HandleMouseMotion(event);
        }
        else
            w->SetMouseOut();
    }
}

void WidgetContainer::PropagateRender()
{
    for(Widget * w : mWidgets)
    {
        w->OnRender();
        w->PropagateRender();
    }
}

} // namespace sgui
} // namespace lib
