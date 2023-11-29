#include "sgl/sgui/AbstractButtonsGroup.h"

#include "sgl/sgui/AbstractButton.h"

#include <cassert>

namespace sgl
{
namespace sgui
{

AbstractButtonsGroup::AbstractButtonsGroup()
    : mOnToggle([](unsigned int, bool){})
{
}

void AbstractButtonsGroup::SetExclusive(bool val)
{
    // value already set
    if(mExclusive == val)
        return ;

    mExclusive = val;

    for(AbstractButton * btn : mButtons)
        btn->SetExclusive(val);
}

void AbstractButtonsGroup::SetButtonChecked(unsigned int index, bool val)
{
    const int ind = static_cast<int>(index);

    if(index >= mButtons.size())
        return ;

    AbstractButton * button = mButtons[index];

    // already set
    if(button->IsChecked() == val)
        return ;

    // update only button if enabled
    if(button->IsEnabled())
        button->SetChecked(val);
}

void AbstractButtonsGroup::SetButtonEnabled(unsigned int index, bool val)
{
    if(index < mButtons.size())
    {
        AbstractButton * button = mButtons[index];

        if(!val && button->IsChecked())
            button->SetChecked(false);

        button->SetEnabled(val);
    }
}

void AbstractButtonsGroup::ClearButtons()
{
    BeforeButtonsCleared();

    for(AbstractButton * b : mButtons)
    {
        const unsigned int fId = mToggleFunctions[b];
        mToggleFunctions.erase(b);

        b->RemoveToggleFunction(fId);
    }

    mIndChecked = -1;

    mButtons.clear();

    OnButtonsCleared();
}

void AbstractButtonsGroup::AddButton(AbstractButton * button)
{
    assert(button);

    const int buttonIndex = static_cast<int>(mButtons.size());

    // if mutually exclusive group button is checkable
    button->SetCheckable(mExclusive);
    button->SetExclusive(mExclusive);

    if(mExclusive)
    {
        const unsigned int fId = button->AddOnToggleFunction([this, buttonIndex](bool checked)
        {
            if(buttonIndex == mIndChecked)
                return ;

            if(checked && mIndChecked > -1)
                mButtons[mIndChecked]->SetChecked(false);

            mIndChecked = buttonIndex;

            mOnToggle(buttonIndex, checked);
        });

        mToggleFunctions.emplace(button, fId);
    }

    mButtons.emplace_back(button);

    // allow subclasses to react to add
    OnButtonAdded(button);
}

void AbstractButtonsGroup::RemoveButton(AbstractButton * button)
{
    auto it = mButtons.begin();

    while(it != mButtons.end())
    {
        if(*it == button)
        {
            mButtons.erase(it);
            mToggleFunctions.erase(button);

            OnButtonRemoved(button);

            return ;
        }

        ++it;
    }
}

void AbstractButtonsGroup::OnButtonAdded(AbstractButton *) { }
void AbstractButtonsGroup::OnButtonRemoved(AbstractButton *) { }
void AbstractButtonsGroup::BeforeButtonsCleared() { }
void AbstractButtonsGroup::OnButtonsCleared() { }

} // namespace sgui
} // namespace sgl
