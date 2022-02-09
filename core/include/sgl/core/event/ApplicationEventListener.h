#pragma once

namespace sgl
{
namespace core
{

class ApplicationEvent;
class EventDispatcher;

class ApplicationEventListener
{
public:
    virtual ~ApplicationEventListener();

private:
    virtual void OnApplicationQuit(ApplicationEvent & event);

private:
    EventDispatcher * mDispatcher = nullptr;

    // only EventDispatcher can generate events
    friend class EventDispatcher;
};

} // namespace core
} // namespace sgl
