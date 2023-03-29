#pragma once

#include "IFilesystem.h"

namespace sgl
{
namespace utilities
{

class FilesystemBase : public IFilesystem
{
public:
    bool CreateDirectory(const std::string & path) const override;
    bool CreateDirectories(const std::string & path) const override;
    bool DoesDirectoryExist(const std::string & path) const override;
};

} // namespace utilities
} // namespace sgl
