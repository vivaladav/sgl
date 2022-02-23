#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

namespace sgl
{
namespace sgui
{

class PushButton;

class AbstractButtonsGroup
{
public:
    typedef std::function<void(unsigned int, bool)> ToggleFun;

public:
    AbstractButtonsGroup();

    bool IsExclusive() const;
    void SetExclusive(bool val);

    int GetIndexChecked() const;
    void SetButtonChecked(unsigned int index, bool val);

    void SetButtonEnabled(unsigned int index, bool val);

    void ClearButtons();
    void AddButton(PushButton * button);
    void RemoveButton(PushButton * button);
    PushButton * GetButton(unsigned int ind) const;

    unsigned int GetNumButtons() const;

    void SetFunctionOnToggle(const ToggleFun & f);

private:
    virtual void OnButtonAdded(PushButton * button);
    virtual void OnButtonRemoved(PushButton * button);
    virtual void OnButtonsCleared();

private:
    std::unordered_map<PushButton *, unsigned int> mToggleFunctions;
    std::vector<PushButton *> mButtons;

    std::function<void(unsigned int, bool)> mOnToggle;

    int mIndChecked = -1;

    bool mExclusive = true;
};

inline bool AbstractButtonsGroup::IsExclusive() const { return mExclusive; }

inline int AbstractButtonsGroup::GetIndexChecked() const{ return mIndChecked; }

inline PushButton * AbstractButtonsGroup::GetButton(unsigned int ind) const
{
    if(ind < mButtons.size())
        return mButtons[ind];
    else
        return nullptr;
}

inline unsigned int AbstractButtonsGroup::GetNumButtons() const { return mButtons.size(); }

inline void AbstractButtonsGroup::SetFunctionOnToggle(const ToggleFun & f) { mOnToggle = f; }

} // namespace sgui
} // namespace sgl
