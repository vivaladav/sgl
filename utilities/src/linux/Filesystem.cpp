#include "sgl/utilities/linux/Filesystem.h"

#include <cstdlib>
#include <pwd.h>
#include <unistd.h>

namespace sgl
{
namespace utilities
{

std::string Filesystem::GetUserHomeDirectory()
{
    // check HOME environment variable
    const char * ret = getenv("HOME");

    if(ret != nullptr)
        return std::string(ret);

    // get home directory from password file entry
    struct passwd * pwd = getpwuid(getuid());

    if(pwd != nullptr)
        return std::string(pwd->pw_dir);

    // everything failed
    return std::string();
}

} // namespace utilities
} // namespace sgl
