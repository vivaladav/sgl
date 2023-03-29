#include "sgl/utilities/FilesystemBase.h"

#include <filesystem>

namespace sgl
{
namespace utilities
{

bool FilesystemBase::DoesDirectoryExist(const std::string & path) const
{
    const std::filesystem::directory_entry d(path);

    return d.is_directory();
}

} // namespace utilities
} // namespace sgl
