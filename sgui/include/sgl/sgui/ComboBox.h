#pragma once

#include "sgl/sgui/AbstractButton.h"

#include <vector>

namespace sgl
{

namespace graphic
{
    class Font;
    class Image;
    class Text;
    class Texture;
}

namespace sgui
{

class ComboBoxItem;

class ComboBox : public AbstractButton
{
public:
    ComboBox(Widget * parent);

    void AddItem(ComboBoxItem * item);

    const ComboBoxItem * GetActiveItem() const;
    int GetActiveItemIndex() const;
    void SetActiveItem(unsigned int index);

    void SetOnActiveChanged(const std::function<void(int)> & f);

protected:
    void SetLabelFont(graphic::Font * font);
    void SetLabelColor(unsigned int color);

    void SetBodyTexture(graphic::Texture * tex);

    void HandlePositionChanged() override;

private:
    void UpdateText();

    void HandleVisibilityChanged(VisibilityChangeEvent & event) override;

private:
    std::vector<ComboBoxItem *> mItems;

    std::function<void(int)> mOnActiveChanged;

    graphic::Image * mBody = nullptr;
    graphic::Text * mLabel = nullptr;
    graphic::Font * mLabelFont = nullptr;

    int mActiveItem = -1;
};

inline const ComboBoxItem * ComboBox::GetActiveItem() const
{
    if(-1 != mActiveItem)
        return mItems[mActiveItem];
    else
        return nullptr;
}

inline int ComboBox::GetActiveItemIndex() const { return mActiveItem; }

inline void ComboBox::SetOnActiveChanged(const std::function<void(int)> & f) { mOnActiveChanged = f; }

} // namespace sgui
} // namespace sgl
