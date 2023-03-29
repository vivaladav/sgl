#include "sgl/utilities/windows/Filesystem.h"

#include <cstdlib>

namespace sgl
{
namespace utilities
{

std::string Filesystem::GetUserHomeDirectory()
{
    const errno_t NO_ERR = 0;

    // check environment variable USERPROFILE
    char * envUsrProf;
    size_t len;

    const errno_t err = _dupenv_s(&envUsrProf, &len, "USERPROFILE");

    if(err == NO_ERR && len > 0)
    {
        const std::string sret(envUsrProf);

        if(DoesDirectoryExist(sret))
            return sret;
    }

    // check environment variables HOME
    char * envDrive;
    char * envPath;
    size_t len1;
    size_t len2;

    const errno_t err1 = _dupenv_s(&envDrive, &len1, "HOMEDRIVE");
    const errno_t err2 = _dupenv_s(&envPath, &len2, "HOMEPATH");

    if(err1 == NO_ERR && len1 > 0 && err2 == NO_ERR && len2 > 0)
    {
        const std::string sret = std::string(envDrive) + std::string(envPath);

        if(DoesDirectoryExist(sret))
            return sret;
    }

    // everything failed
    return std::string();
}

} // namespace utilities
} // namespace sgl
