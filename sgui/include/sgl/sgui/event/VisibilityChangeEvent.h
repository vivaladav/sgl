#pragma once

#include "sgl/core/event/Event.h"

namespace sgl
{
namespace sgui
{

class VisibilityChangeEvent : public core::Event
{
public:
    VisibilityChangeEvent(bool visible);

    bool IsVisible() const;

private:
    bool mVisible = false;
};

inline VisibilityChangeEvent::VisibilityChangeEvent(bool visible) : mVisible(visible) {}

inline bool VisibilityChangeEvent::IsVisible() const { return mVisible; }

} // namespace sgui
} // namespace sgl
