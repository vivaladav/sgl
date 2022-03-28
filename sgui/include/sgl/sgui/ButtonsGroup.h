#pragma once

#include "sgl/sgui/AbstractButtonsGroup.h"
#include "sgl/sgui/Widget.h"

namespace sgl
{
namespace sgui
{

class AbstractButton;

class ButtonsGroup : public AbstractButtonsGroup, public Widget
{
public:
    enum Orientation
    {
        HORIZONTAL,
        VERTICAL
    };

public:
    ButtonsGroup(Orientation orient, Widget * parent = nullptr);

    void SetSpacing(int spacing);

    void OnButtonAdded(AbstractButton * button) override;
    void OnButtonRemoved(AbstractButton * button) override;
    void OnButtonsCleared() override;

private:
    void RepositionButtons();

private:
    Orientation mOrient;

    int mSpacing = 0;
};

inline void ButtonsGroup::SetSpacing(int spacing) { mSpacing = spacing; }

} // namespace sgui
} // namespace sgl
