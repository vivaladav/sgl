#pragma once

#include <vector>

namespace sgl
{
namespace core
{

class ApplicationEventListener;
class KeyboardEventListener;
class MouseEventListener;
class WindowEventHandler;

class EventDispatcher
{
public:
    void AddApplicationListener(ApplicationEventListener * el);
    void AddKeyboardListener(KeyboardEventListener * el);
    void AddMouseListener(MouseEventListener * el);

    void RemoveApplicationListener(ApplicationEventListener * el);
    void RemoveKeyboardListener(KeyboardEventListener * el);
    void RemoveMouseListener(MouseEventListener * el);

    void SetWindowEventHandler(WindowEventHandler * handler);

    void Update();

private:
    std::vector<ApplicationEventListener *> mApplicationListeners;
    std::vector<KeyboardEventListener *> mKeyboardListeners;
    std::vector<MouseEventListener *> mMouseListeners;

    WindowEventHandler * mWindowEventHandler = nullptr;
};

inline void EventDispatcher::SetWindowEventHandler(WindowEventHandler * handler)
{
    mWindowEventHandler = handler;
}

} // namespace core
} // namespace sgl

