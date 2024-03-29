#include "sgl/sgui/Slider.h"

#include "sgl/graphic/Image.h"

#include <cmath>

namespace sgl
{
namespace sgui
{

Slider::Slider(Orientation o, Widget * parent)
    : AbstractSlider(o, parent)
{
    mBg = new graphic::Image;
    RegisterRenderable(mBg);

    mBar = new graphic::Image;
    RegisterRenderable(mBar);

    mButton = new graphic::Image;
    RegisterRenderable(mButton);
}

} // namespace sgui
} // namespace sgl
