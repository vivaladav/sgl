#include "sgl/utilities/linux/Filesystem.h"

#include <cstdlib>
#include <pwd.h>
#include <unistd.h>

namespace sgl
{
namespace utilities
{

std::string Filesystem::GetUserHomeDirectory() const
{
    // check HOME environment variable
    const char * ret = getenv("HOME");

    if(ret != nullptr)
    {
        const std::string sret(ret);

        if(DoesDirectoryExist(sret))
            return sret;
    }

    // get home directory from password file entry
    struct passwd * pwd = getpwuid(getuid());

    if(pwd != nullptr)
    {
        const std::string sret(pwd->pw_dir);

        if(DoesDirectoryExist(sret))
            return sret;
    }

    // everything failed
    return std::string();
}

} // namespace utilities
} // namespace sgl
