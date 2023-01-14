#pragma once

namespace sgl
{
namespace graphic
{

class Window;
class WindowEvent;

class WindowEventListener
{
public:
    virtual ~WindowEventListener();

private:
    virtual void OnWindowMinimized(WindowEvent & event);
    virtual void OnWindowMaximized(WindowEvent & event);
    virtual void OnWindowMouseEntered(WindowEvent & event);
    virtual void OnWindowMouseLeft(WindowEvent & event);
    virtual void OnWindowKeyboardFocusGained(WindowEvent & event);
    virtual void OnWindowKeyboardFocusLost(WindowEvent & event);
    virtual void OnWindowExposed(WindowEvent & event);
    virtual void OnWindowHidden(WindowEvent & event);

private:
    Window * mWindow = nullptr;

    // only Window can generate events
    friend class Window;
};

} // namespace graphic
} // namespace sgl
