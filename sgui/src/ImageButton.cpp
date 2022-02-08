#include "sgl/sgui/ImageButton.h"

#include "sgl/graphic/Image.h"
#include "sgl/graphic/Texture.h"
#include "sgl/graphic/TextureManager.h"

namespace lib
{
namespace sgui
{

ImageButton::ImageButton(const std::array<unsigned int, NUM_VISUAL_STATES> & texIds,
            const char * spriteFile, lib::sgui::Widget * parent)
    : lib::sgui::PushButton(parent)
    , mBody(new lib::graphic::Image)
{
    RegisterRenderable(mBody);

    for(unsigned int i = 0; i < NUM_VISUAL_STATES; ++i)
    {
        auto tm = lib::graphic::TextureManager::Instance();
        mTexs[i] = tm->GetSprite(spriteFile, texIds[i]);
    }

    // set initial visual state
    SetState(NORMAL);
}

void ImageButton::OnStateChanged(lib::sgui::PushButton::VisualState state)
{
    mBody->SetTexture(mTexs[state]);
    // reset BG to make changes visible
    SetCurrBg(mBody);
}

} // namespace sgui
} // namespace lib
