#pragma once

#include "sgl/sgui/Widget.h"

namespace sgl
{
namespace sgui
{

class ScrollArea : public Widget
{
public:
    ScrollArea(int w, int h, Widget * parent);

    Widget * GetContent() const;
    void SetContent(Widget * content);

private:
    virtual void HandleNewContent();

private:
    Widget * mContent = nullptr;
};

inline Widget * ScrollArea::GetContent() const { return mContent; }

} // namespace sgui
} // namespace sgl
