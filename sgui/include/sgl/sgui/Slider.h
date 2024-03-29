#pragma once

#include "sgl/sgui/AbstractSlider.h"

namespace sgl
{

namespace graphic { class Image; }

namespace sgui
{

class Slider : public AbstractSlider
{

public:
    Slider(Orientation o, Widget * parent);

protected:
    graphic::Image * mBg = nullptr;
    graphic::Image * mBar = nullptr;
    graphic::Image * mButton = nullptr;
};

} // namespace sgui
} // namespace sgl
