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

private:
    std::string mText;
};

inline const std::string ComboBoxItem::GetText() const { return mText; }

} // namespace sgui
} // namespace sgl
