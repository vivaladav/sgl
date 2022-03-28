#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

namespace sgl
{
namespace sgui
{

class AbstractButton;

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
    void AddButton(AbstractButton * button);
    void RemoveButton(AbstractButton * button);
    AbstractButton *GetButton(unsigned int ind) const;

    unsigned int GetNumButtons() const;

    void SetFunctionOnToggle(const ToggleFun & f);

private:
    virtual void OnButtonAdded(AbstractButton * button);
    virtual void OnButtonRemoved(AbstractButton * button);
    virtual void OnButtonsCleared();

private:
    std::unordered_map<AbstractButton *, unsigned int> mToggleFunctions;
    std::vector<AbstractButton *> mButtons;

    std::function<void(unsigned int, bool)> mOnToggle;

    int mIndChecked = -1;

    bool mExclusive = true;
};

inline bool AbstractButtonsGroup::IsExclusive() const { return mExclusive; }

inline int AbstractButtonsGroup::GetIndexChecked() const{ return mIndChecked; }

inline AbstractButton * AbstractButtonsGroup::GetButton(unsigned int ind) const
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
