#include "sgl/graphic/ModuleGraphic.h"

#ifdef LINUX
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

#include <iostream>

namespace sgl
{
namespace graphic
{

void ModuleGraphic::PrintBuildLibs()
{
    SDL_version imgVer;
    SDL_version ttfVer;

    SDL_IMAGE_VERSION(&imgVer);
    SDL_TTF_VERSION(&ttfVer);

    std::cout << "====== GRAPHIC - BUILD LIBRARIES ======" << std::endl;
    std::cout << "SDL_image version: "
              << static_cast<int>(imgVer.major) << "."
              << static_cast<int>(imgVer.minor) << "."
              << static_cast<int>(imgVer.patch) << std::endl;
    std::cout << "SDL_ttf version: "
              << static_cast<int>(ttfVer.major) << "."
              << static_cast<int>(ttfVer.minor) << "."
              << static_cast<int>(ttfVer.patch) << std::endl;
    std::cout << "---------------------------------------" << std::endl;
}

void ModuleGraphic::PrintRuntimeLibs()
{

    const SDL_version * imgVer = IMG_Linked_Version();
    const SDL_version * ttfVer = TTF_Linked_Version();

    std::cout << "====== GRAPHIC - RUNTIME LIBRARIES ======" << std::endl;
    std::cout << "SDL_image version: "
              << static_cast<int>(imgVer->major) << "."
              << static_cast<int>(imgVer->minor) << "."
              << static_cast<int>(imgVer->patch) << std::endl;
    std::cout << "SDL_ttf version: "
              << static_cast<int>(ttfVer->major) << "."
              << static_cast<int>(ttfVer->minor) << "."
              << static_cast<int>(ttfVer->patch) << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
}

} // namespace graphic
} // namespace sgl
