#pragma once

#include <list>

namespace sgl
{

namespace core
{
    class KeyboardEvent;
    class MouseButtonEvent;
    class MouseMotionEvent;
    class MouseWheelEvent;
}

namespace sgui
{

class VisibilityChangeEvent;
class Widget;

class WidgetContainer
{
public:
    virtual ~WidgetContainer();

    void ClearWidgets();

    int GetNumChildren() const;

    void MoveChildToBack(Widget * w);
    void MoveChildToFront(Widget * w);

    void ClearFocus();
    void SetFocus();
    bool HasFocus() const;

    virtual void SetVisible(bool val);
    bool IsVisible() const;

protected:
    void AddChild(Widget * w);
    void RemoveChild(Widget * w);

    virtual void HandleChildEnableChanged(Widget * child);
    virtual void HandleChildVisibleChanged(Widget * child);

    void PropagateMouseButtonDown(core::MouseButtonEvent & event);
    void PropagateMouseButtonUp(core::MouseButtonEvent & event);
    void PropagateMouseMotion(core::MouseMotionEvent & event);
    void PropagateMouseWheel(core::MouseWheelEvent & event);

    void PropagateKeyDown(core::KeyboardEvent & event);
    void PropagateKeyUp(core::KeyboardEvent & event);

    virtual void HandleVisibilityChanged(VisibilityChangeEvent & event);
    void PropagateVisibilityChanged(VisibilityChangeEvent & event);

    void PropagateRender();

    void PropagateFocus();

    void PropagateUpdate(float delta);

protected:
    std::list<Widget *> mWidgets;

private:
    bool mFocus = false;
    bool mVisible = true;
};

inline int WidgetContainer::GetNumChildren() const { return mWidgets.size(); }

inline bool WidgetContainer::HasFocus() const { return mFocus; }

inline bool WidgetContainer::IsVisible() const { return mVisible; }

} // namespace sgui
} // namespace sgl
