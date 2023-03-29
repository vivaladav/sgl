#pragma once

#include "sgl/utilities/FilesystemBase.h"

namespace sgl
{
namespace utilities
{

class Filesystem : public FilesystemBase
{
public:
    std::string GetUserHomeDirectory() const override;
};

} // namespace utilities
} // namespace sgl
