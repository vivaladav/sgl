#pragma once

union SDL_Event;

namespace sgl
{
namespace core
{

class WindowEventHandler
{
public:
    virtual ~WindowEventHandler() = default;

    virtual void HandleEvent(const union SDL_Event & event) = 0;
};

} // namespace core
} // namespace sgl
