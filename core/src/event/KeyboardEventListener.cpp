#include "sgl/core/event/KeyboardEventListener.h"

#include "EventDispatcher.h"

namespace sgl
{
namespace core
{

KeyboardEventListener::~KeyboardEventListener()
{
    if(mDispatcher)
        mDispatcher->RemoveKeyboardListener(this);
}

void KeyboardEventListener::OnKeyDown(KeyboardEvent &) { }
void KeyboardEventListener::OnKeyUp(KeyboardEvent &) { }

} // namespace core
} // namespace sgl
