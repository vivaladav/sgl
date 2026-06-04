#pragma once

#include <functional>
#include <map>
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
    virtual ~AbstractButtonsGroup() = default;

    bool IsExclusive() const;
    void SetExclusive(bool val);

    int GetIndexChecked() const;
    void SetButtonChecked(unsigned int index, bool val);

    void SetButtonEnabled(unsigned int index, bool val);

    void ClearButtons();
    void AddButton(AbstractButton * button);
    void RemoveButton(AbstractButton * button);
    AbstractButton * GetButton(unsigned int ind) const;

    unsigned int GetNumButtons() const;

    unsigned int AddFunctionOnToggle(const std::function<void(unsigned int, bool)> & f);
    void RemoveFunctionOnToggle(unsigned int fId);

private:
    virtual void OnButtonAdded(AbstractButton * button);
    virtual void OnButtonRemoved(AbstractButton * button);
    virtual void BeforeButtonsCleared();
    virtual void OnButtonsCleared();

private:
    std::unordered_map<AbstractButton *, unsigned int> mToggleFunctions;
    std::vector<AbstractButton *> mButtons;

    std::map<unsigned int, std::function<void(unsigned int, bool)>> mOnToggle;

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

} // namespace sgui
} // namespace sgl
