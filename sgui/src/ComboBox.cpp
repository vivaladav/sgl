#include "sgl/sgui/ComboBox.h"

#include "sgl/graphic/Image.h"
#include "sgl/graphic/Text.h"
#include "sgl/sgui/ComboBoxItem.h"

namespace sgl
{
namespace sgui
{

ComboBox::ComboBox(Widget * parent)
    : AbstractButton(parent)
{        
    mBody = new graphic::Image;
    RegisterRenderable(mBody);

    SetCheckable(true);

    AddOnToggleFunction([this](bool checked)
    {
        for(ComboBoxItem * item : mItems)
            item->SetVisible(checked);
    });

    SetState(NORMAL);
}

void ComboBox::AddItem(ComboBoxItem * item)
{
    const int numItems = mItems.size();

    item->SetVisible(false);
    mItems.push_back(item);

    item->AddOnClickFunction([this, numItems]
    {
        SetChecked(false);

        SetActiveItem(numItems);

        // hide items
        for(ComboBoxItem * item : mItems)
            item->SetVisible(false);
    });

    if(-1 == mActiveItem)
        SetActiveItem(0);
}

void ComboBox::SetActiveItem(unsigned int index)
{
    // iteam already active -> exit
    if(static_cast<int>(index) == mActiveItem)
        return ;

    mActiveItem = index;

    UpdateText();
}

void ComboBox::SetLabelFont(graphic::Font * font)
{
    mLabelFont = font;
}

void ComboBox::SetLabelColor(unsigned int color)
{
    mLabel->SetColor(color);
}

void ComboBox::SetBodyTexture(graphic::Texture * tex)
{
    mBody->SetTexture(tex);

    SetSize(mBody->GetWidth(), mBody->GetHeight());
}

void ComboBox::HandlePositionChanged()
{
    const int x0 = GetScreenX();
    const int y0 = GetScreenY();
    const int w0 = mBody->GetWidth();
    const int h0 = mBody->GetHeight();

    // position BODY
    mBody->SetPosition(x0, y0);

    // position LABEL
    const int labelX = x0 + (w0 - mLabel->GetWidth()) * 0.5f;
    const int labelY = y0 + (h0 - mLabel->GetHeight()) * 0.5f;
    mLabel->SetPosition(labelX, labelY);

    // position ITEMS
    int y = y0 + h0;

    for(ComboBoxItem * item : mItems)
    {
        item->SetPosition(x0, y);

        y += item->GetHeight();
    }
}

void ComboBox::UpdateText()
{
    if(mLabel)
    {
        UnregisterRenderable(mLabel);
        delete mLabel;
    }

    mLabel = new graphic::Text(mItems[mActiveItem]->GetText().c_str(), mLabelFont);
    RegisterRenderable(mLabel);

    HandlePositionChanged();

    OnStateChanged(GetState());
}

} // namespace sgui
} // namespace sgl
