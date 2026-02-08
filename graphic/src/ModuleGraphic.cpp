#include "sgl/graphic/ModuleGraphic.h"

#include "sgl/graphic/Renderer.h"

#ifdef LINUX
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL.h>
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

void ModuleGraphic::PrintVideoInfo()
{
    auto r = Renderer::Instance();

    if(r == nullptr)
        return ;

    std::cout << "=========== GRAPHIC - VIDEO INFO ===========" << std::endl;
    r->PrintInfo();

    std::cout << "ACTIVE VIDEO DRIVER: " << SDL_GetCurrentVideoDriver() << std::endl;

    const int numDrivers = SDL_GetNumVideoDrivers();
    const int lastDriver = numDrivers - 1;
    std::cout << "AVAILABLE VIDEO DRIVERS: ";
    for(int i = 0; i < lastDriver; ++i)
        std::cout << SDL_GetVideoDriver(i) << ", ";

    if(lastDriver > 0)
        std::cout << SDL_GetVideoDriver(lastDriver) << "\n";

    std::cout << "--------------------------------------------" << std::endl;
}

// -- cursor --
void ModuleGraphic::HideSystemCursor()
{
    SDL_ShowCursor(SDL_DISABLE);
}

void ModuleGraphic::ShowSystemCursor()
{
    SDL_ShowCursor(SDL_ENABLE);
}

} // namespace graphic
} // namespace sgl
