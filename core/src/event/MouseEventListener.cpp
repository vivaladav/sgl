#include "sgl/core/event/MouseEventListener.h"

#include "EventDispatcher.h"

namespace sgl
{
namespace core
{

MouseEventListener::~MouseEventListener()
{
    if(mDispatcher)
        mDispatcher->RemoveMouseListener(this);
}

void MouseEventListener::OnMouseButtonDown(MouseButtonEvent &) { }
void MouseEventListener::OnMouseButtonUp(MouseButtonEvent &) { }
void MouseEventListener::OnMouseMotion(MouseMotionEvent &) { }
void MouseEventListener::OnMouseWheel(MouseWheelEvent &) { }

} // namespace core
} // namespace sgl
