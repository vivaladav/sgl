#include "sgl/graphic/event/WindowEventListener.h"

#include "sgl/graphic/Window.h"

namespace sgl
{
namespace graphic
{

WindowEventListener::~WindowEventListener()
{
    if(mWindow)
        mWindow->RemoveWindowListener(this);
}

void WindowEventListener::OnWindowMinimized(WindowEvent & event) { }
void WindowEventListener::OnWindowMaximized(WindowEvent & event) { }
void WindowEventListener::OnWindowMouseEntered(WindowEvent & event) { }
void WindowEventListener::OnWindowMouseLeft(WindowEvent & event) { }
void WindowEventListener::OnWindowKeyboardFocusGained(WindowEvent & event) { }
void WindowEventListener::OnWindowKeyboardFocusLost(WindowEvent & event) { }
void WindowEventListener::OnWindowExposed(WindowEvent & event) { }
void WindowEventListener::OnWindowHidden(WindowEvent & event) { }

} // namespace graphic
} // namespace sgl
