#pragma once

#include "sgl/sgui/PushButton.h"

#include <array>

namespace sgl
{

namespace graphic
{
    class Image;
    class Texture;
}

namespace sgui
{

class ImageButton : public PushButton
{
public:
    ImageButton(const std::array<unsigned int, NUM_VISUAL_STATES> & texIds,
                const char * spriteFile, Widget *parent);

protected:
    void OnStateChanged(sgl::sgui::AbstractButton::VisualState state) override;

private:
    std::array<sgl::graphic::Texture *, NUM_VISUAL_STATES> mTexs;

    sgl::graphic::Image * mBody = nullptr;
};

} // namespace sgui
} // namespace sgl
