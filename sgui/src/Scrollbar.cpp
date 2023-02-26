#include "sgl/sgui/Scrollbar.h"

#include "sgl/graphic/Image.h"

#include <cmath>

namespace sgl
{
namespace sgui
{

Scrollbar::Scrollbar(Orientation o, Widget * parent)
    : AbstractSlider(o, parent)
{
    mBg = new graphic::Image;
    RegisterRenderable(mBg);

    mButton = new graphic::Image;
    RegisterRenderable(mButton);
}

} // namespace sgui
} // namespace sgl
