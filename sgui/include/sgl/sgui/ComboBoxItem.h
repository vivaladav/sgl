#pragma once

#include "sgl/sgui/AbstractButton.h"

#include <string>

namespace sgl
{
namespace sgui
{

class ComboBoxItem : public AbstractButton
{
public:
    ComboBoxItem(const char * text);

    const std::string GetText() const;

protected:
    void SetText(const char * text);

private:
    std::string mText;
};

inline const std::string ComboBoxItem::GetText() const { return mText; }

inline void ComboBoxItem::SetText(const char * text) { mText = text; }

} // namespace sgui
} // namespace sgl
