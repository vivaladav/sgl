#include "sgl/utilities/windows/System.h"

#include <windows.h>

namespace sgl
{
namespace utilities
{

bool System::OpenUrlInBrowser(const std::string & url)
{
    const INT_PTR okThresh = 32;
    const INT_PTR res = reinterpret_cast<INT_PTR>(ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL));

    return res > okThresh;
}

} // namespace utilities
} // namespace sgl
