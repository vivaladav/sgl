#include "sgl/sgui/ImageButton.h"

#include "sgl/graphic/Image.h"
#include "sgl/graphic/Texture.h"
#include "sgl/graphic/TextureManager.h"

namespace sgl
{
namespace sgui
{

ImageButton::ImageButton(const std::array<unsigned int, NUM_VISUAL_STATES> & texIds,
            const char * spriteFile, Widget * parent)
    : PushButton(parent)
    , mBody(new sgl::graphic::Image)
{
    RegisterRenderable(mBody);

    for(unsigned int i = 0; i < NUM_VISUAL_STATES; ++i)
    {
        auto tm = sgl::graphic::TextureManager::Instance();
        mTexs[i] = tm->GetSprite(spriteFile, texIds[i]);
    }

    // set initial visual state
    SetState(NORMAL);
}

void ImageButton::OnStateChanged(sgl::sgui::PushButton::VisualState state)
{
    mBody->SetTexture(mTexs[state]);
    // reset BG to make changes visible
    SetCurrBg(mBody);
}

} // namespace sgui
} // namespace sgl
