#include "sgl/core/event/ApplicationEventListener.h"

#include "EventDispatcher.h"

namespace sgl
{
namespace core
{

ApplicationEventListener::~ApplicationEventListener()
{
    if(mDispatcher)
        mDispatcher->RemoveApplicationListener(this);
}

void ApplicationEventListener::OnApplicationQuit(ApplicationEvent &) { }

} // namespace core
} // namespace sgl
