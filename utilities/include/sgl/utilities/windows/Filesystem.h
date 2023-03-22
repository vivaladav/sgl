#pragma once

#include "sgl/utilities/IFilesystem.h"

namespace sgl
{
namespace utilities
{

class Filesystem : public IFilesystem
{
public:
    std::string GetUserHomeDirectory() override;
};

} // namespace utilities
} // namespace sgl
