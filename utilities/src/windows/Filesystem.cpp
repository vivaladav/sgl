#include "sgl/utilities/linux/Filesystem.h"

#include <cstdlib>

namespace sgl
{
namespace utilities
{

std::string Filesystem::GetUserHomeDirectory()
{
    // check environment variables
    const char * envDrive = getenv("HOMEDRIVE");
    const char * envPath = getenv("HOMEPATH");

    if(envDrive != nullptr && envPath != nullptr)
        return std::string(envDrive) + std::string(envPath);

    // everything failed
    return std::string();
}

} // namespace utilities
} // namespace sgl
