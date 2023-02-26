#pragma once

#include "sgl/sgui/AbstractSlider.h"

namespace sgl
{

namespace graphic { class Image; }

namespace sgui
{

class Scrollbar : public AbstractSlider
{

public:
    Scrollbar(Orientation o, Widget * parent);

protected:
    graphic::Image * mBg = nullptr;
    graphic::Image * mButton = nullptr;

};

} // namespace sgui
} // namespace sgl
