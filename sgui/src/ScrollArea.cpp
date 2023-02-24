#include "sgl/sgui/ScrollArea.h"

namespace sgl
{
namespace sgui
{

ScrollArea::ScrollArea(int w, int h, Widget * parent)
    : Widget(parent)
{
    SetSize(w, h);
    SetResizePolicy(FIXED);
}

void ScrollArea::SetContent(Widget * content)
{
    if(content == mContent)
        return ;

    mContent = content;

    if(mContent)
        mContent->SetParent(this);

    HandleNewContent();
}

void ScrollArea::HandleNewContent() { }

} // namespace sgui
} // namespace sgl
