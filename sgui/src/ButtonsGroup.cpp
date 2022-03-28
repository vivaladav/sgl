#include "sgl/sgui/ButtonsGroup.h"

#include "sgl/sgui/AbstractButton.h"

#include <cassert>

namespace sgl
{
namespace sgui
{

ButtonsGroup::ButtonsGroup(Orientation orient, Widget * parent)
    : Widget(parent)
    , mOrient(orient)
{
}

void ButtonsGroup::OnButtonAdded(AbstractButton * button)
{
    const int w = GetWidth();
    const int h = GetHeight();

    // no spacing when adding the first button (w=0)
    const int spacing = w > 0 ? mSpacing : 0;

    // this will update the size of the group
    button->SetParent(this);

    int x = 0;
    int y = 0;

    if(mOrient == HORIZONTAL)
        x += w + spacing;
    else
        y += h + spacing;

    // button's position depends on orientation
    button->SetPosition(x, y);
}

void ButtonsGroup::OnButtonRemoved(AbstractButton * button)
{
    RepositionButtons();
}

void ButtonsGroup::OnButtonsCleared()
{
    SetSize(0, 0);
}

void ButtonsGroup::RepositionButtons()
{
    int x = 0;
    int y = 0;

    for(unsigned int i = 0; i < GetNumButtons(); ++i)
    {
        auto button = GetButton(i);
        button->SetPosition(x, y);

        if(mOrient == HORIZONTAL)
            x += button->GetWidth() + mSpacing;
        else
            y += button->GetHeight() + mSpacing;
    }
}

} // namespace sgui
} // namespace sgl
