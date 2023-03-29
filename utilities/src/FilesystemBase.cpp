#include "sgl/utilities/FilesystemBase.h"

#include <filesystem>

namespace sgl
{
namespace utilities
{

bool FilesystemBase::CreateDirectory(const std::string & path) const
{
    return std::filesystem::create_directory(path);
}

bool FilesystemBase::CreateDirectories(const std::string & path) const
{
    return std::filesystem::create_directories(path);
}

bool FilesystemBase::DoesDirectoryExist(const std::string & path) const
{
    const std::filesystem::directory_entry d(path);

    return d.is_directory();
}

} // namespace utilities
} // namespace sgl
