#include "sgl/sgui/AbstractButton.h"

#include "sgl/core/event/KeyboardEvent.h"
#include "sgl/core/event/MouseButtonEvent.h"

namespace sgl
{
namespace sgui
{

AbstractButton::AbstractButton(Widget * parent)
    : Widget(parent)
{
}

void AbstractButton::SetChecked(bool val)
{
    if(val != mChecked)
    {
        mChecked = val;
        HandleCheckedChanged(mChecked);

        for(auto & it : mOnToggle)
            it.second(mChecked);
    }
}

void AbstractButton::Click()
{
    // checkable button
    if(mCheckable)
    {
        mChecked = !mChecked;

        HandleCheckedChanged(mChecked);

        for(auto & it : mOnToggle)
            it.second(mChecked);
    }
    // standard button
    else
        for(auto & it: mOnClick)
            it.second();
}

unsigned int AbstractButton::AddOnClickFunction(const std::function<void()> & f)
{
    static unsigned int num = 0;

    int fId = ++num;
    mOnClick.emplace(fId, f);

    return fId;
}

void AbstractButton::RemoveClickFunction(unsigned int fId)
{
    auto it = mOnClick.find(fId);

    if(it != mOnClick.end())
        mOnClick.erase(it);
}

unsigned int AbstractButton::AddOnToggleFunction(const std::function<void(bool)> & f)
{
    static unsigned int num = 0;

    int fId = ++num;
    mOnToggle.emplace(fId, f);

    return fId;
}

void AbstractButton::RemoveToggleFunction(unsigned int fId)
{
    auto it = mOnToggle.find(fId);

    if(it != mOnToggle.end())
        mOnToggle.erase(it);
}

void AbstractButton::HandleStateEnabled()
{
    if(IsChecked())
        SetState(CHECKED);
    else
        SetState(NORMAL);
}
void AbstractButton::HandleStateDisabled()
{
     SetState(DISABLED);
}

void AbstractButton::HandleMouseButtonDown(sgl::core::MouseButtonEvent & event)
{
    if(!IsEnabled())
        return ;

    HandleButtonDown();

    event.SetConsumed();
}

void AbstractButton::HandleMouseButtonUp(core::MouseButtonEvent & event)
{
    if(!IsEnabled())
        return ;

    HandleButtonUp();

    event.SetConsumed();
}

void AbstractButton::HandleMouseOver()
{
    if(!IsEnabled() || IsChecked())
        return ;

    SetState(MOUSE_OVER);
}

void AbstractButton::HandleMouseOut()
{
    if(!IsEnabled() || IsChecked())
        return ;

    SetState(NORMAL);
}

void AbstractButton::HandleKeyDown(sgl::core::KeyboardEvent & event)
{
    if(event.GetKey() == mShortcutKey)
    {
        HandleButtonDown();

        event.SetConsumed();
    }
}

void AbstractButton::HandleKeyUp(sgl::core::KeyboardEvent & event)
{
    if(event.GetKey() == mShortcutKey)
    {
        HandleButtonUp();

        event.SetConsumed();
    }
}

void AbstractButton::HandleCheckedChanged(bool checked)
{
    SetState(checked ? CHECKED : NORMAL);
}

void AbstractButton::OnStateChanged(VisualState state) { }

void AbstractButton::HandleButtonDown()
{
    if(IsCheckable())
        SetState(CHECKED);
    else
        SetState(PUSHED);
}

void AbstractButton::HandleButtonUp()
{
    // do not uncheck if exclusive (in button group)
    if(mExclusive && mChecked)
        return ;

    // set default state then handle click
    if(IsMouseOver())
        SetState(MOUSE_OVER);
    else
        SetState(NORMAL);

    Click();
}

void AbstractButton::SetState(VisualState state)
{
    if(mState == state)
        return ;

    mState = state;

    OnStateChanged(state);
}

} // namespace sgui
} // namespace sgl
