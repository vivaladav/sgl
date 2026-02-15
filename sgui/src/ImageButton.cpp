#include "sgl/sgui/ImageButton.h"

#include "sgl/graphic/Image.h"
#include "sgl/graphic/TextureManager.h"

namespace sgl
{
namespace sgui
{

ImageButton::ImageButton(const std::array<unsigned int, NUM_VISUAL_STATES> & texIds,
            const char * spriteFile, Widget * parent)
    : AbstractButton(parent)
    , mBody(new sgl::graphic::Image)
{
    RegisterRenderable(mBody);

    for(unsigned int i = 0; i < NUM_VISUAL_STATES; ++i)
    {
        auto tm = sgl::graphic::TextureManager::Instance();
        mTexs[i] = tm->GetSprite(spriteFile, texIds[i]);
    }

    // set initial visual state
    InitState(NORMAL);
    UpdateContent(NORMAL);
}

void ImageButton::OnStateChanged(sgl::sgui::AbstractButton::VisualState state)
{
    AbstractButton::OnStateChanged(state);

    UpdateContent(state);
}

void ImageButton::HandlePositionChanged()
{
    mBody->SetPosition(GetScreenX(), GetScreenY());
}

void ImageButton::UpdateContent(sgui::AbstractButton::VisualState state)
{
    mBody->SetTexture(mTexs[state]);

    mBody->SetPosition(GetScreenX(), GetScreenY());

    SetSize(mBody->GetWidth(), mBody->GetHeight());
}

} // namespace sgui
} // namespace sgl
