#pragma once

#include "sgl/utilities/ISystem.h"

namespace sgl
{
namespace utilities
{

class System : public ISystem
{
public:
    bool OpenUrlInBrowser(const std::string & url) override;
};

} // namespace utilities
} // namespace sgl
