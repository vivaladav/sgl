#include "sgl/sgui/Slider.h"

#include "sgl/graphic/Image.h"

namespace sgl
{
namespace sgui
{

Slider::Slider(Orientation o, Widget * parent)
    : Widget(parent)
    , mOrientation(o)
{
    mBg = new graphic::Image;
    RegisterRenderable(mBg);

    mBar = new graphic::Image;
    RegisterRenderable(mBar);

    mButton = new graphic::Image;
    RegisterRenderable(mButton);
}

void Slider::HandleMouseButtonDown(core::MouseButtonEvent & event)
{
    mDragging = true;
}

void Slider::HandleMouseButtonUp(core::MouseButtonEvent & event)
{
    mDragging = false;
}

void Slider::HandleMouseMotion(core::MouseMotionEvent & event)
{

}

void Slider::OnStateChanged(VisualState) { }

} // namespace sgui
} // namespace sgl
