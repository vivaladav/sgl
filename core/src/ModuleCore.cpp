#include "sgl/core/ModuleCore.h"

#ifdef LINUX
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <iostream>

namespace sgl
{
namespace core
{

void ModuleCore::PrintBuildLibs()
{
    SDL_version sdlVer;
    SDL_VERSION(&sdlVer);

    std::cout << "====== CORE - BUILD LIBRARIES ======" << std::endl;
    std::cout << "SDL version: "
              << static_cast<int>(sdlVer.major) << "."
              << static_cast<int>(sdlVer.minor) << "."
              << static_cast<int>(sdlVer.patch) << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

void ModuleCore::PrintRuntimeLibs()
{
    SDL_version sdlVer;
    SDL_GetVersion(&sdlVer);

    std::cout << "======  CORE - RUNTIME LIBRARIES ======" << std::endl;
    std::cout << "SDL version: "
              << static_cast<int>(sdlVer.major) << "."
              << static_cast<int>(sdlVer.minor) << "."
              << static_cast<int>(sdlVer.patch) << std::endl;
    std::cout << "---------------------------------------" << std::endl;
}

} // namespace core
} // namespace sgl
