#pragma once

#include "MouseEvent.h"

namespace sgl
{
namespace core
{

class EventDispatcher;

class MouseWheelEvent : public MouseEvent
{
public:
    int GetX() const;
    int GetY() const;

    bool ScrollingDown() const;
    bool ScrollingUp() const;
    bool ScrollingLeft() const;
    bool ScrollingRight() const;

private:
    MouseWheelEvent(int x, int y);

private:
    int mX;
    int mY;

    // only EventDispatcher can create an event
    friend class EventDispatcher;
};

inline MouseWheelEvent::MouseWheelEvent(int x, int y)
    : mX(x)
    , mY(y)
{
}

inline int MouseWheelEvent::GetX() const { return mX; }
inline int MouseWheelEvent::GetY() const { return mY; }

inline bool MouseWheelEvent::ScrollingDown() const { return  mY < 0; }
inline bool MouseWheelEvent::ScrollingUp() const { return  mY > 0; }
inline bool MouseWheelEvent::ScrollingLeft() const { return  mX < 0; }
inline bool MouseWheelEvent::ScrollingRight() const { return  mX > 0; }

} // namespace core
} // namespace sgl
