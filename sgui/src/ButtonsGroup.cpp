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
    // make sure button is child of this group
    button->SetParent(this);

    // position the new button according to orientation
    unsigned int numOldButtons = GetNumButtons() - 1;

    int x = 0;
    int y = 0;

    if(mOrient == HORIZONTAL)
    {
        for(unsigned int i = 0; i < numOldButtons; ++i)
            x += GetButton(i)->GetWidth() + mSpacing;
    }
    else
    {
        for(unsigned int i = 0; i < numOldButtons; ++i)
            y += GetButton(i)->GetHeight() + mSpacing;
    }

    button->SetPosition(x, y);
}

void ButtonsGroup::OnButtonRemoved(AbstractButton * button)
{
    RepositionButtons();
}

void ButtonsGroup::BeforeButtonsCleared()
{
    for(unsigned int i = 0; i < GetNumButtons(); ++i)
    {
        auto button = GetButton(i);
        button->SetParent(nullptr);
    }
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
