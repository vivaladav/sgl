#pragma once

#include "sgl/sgui/AbstractButton.h"

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

class ImageButton : public AbstractButton
{
public:
    ImageButton(const std::array<unsigned int, NUM_VISUAL_STATES> & texIds,
                const char * spriteFile, Widget * parent);

protected:
    void OnStateChanged(sgui::AbstractButton::VisualState state) override;

    void HandlePositionChanged() override;

private:
    void UpdateContent(sgui::AbstractButton::VisualState state);

private:
    std::array<graphic::Texture *, NUM_VISUAL_STATES> mTexs;

    graphic::Image * mBody = nullptr;
};

} // namespace sgui
} // namespace sgl
