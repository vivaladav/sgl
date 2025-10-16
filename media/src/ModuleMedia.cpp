#include "sgl/media/ModuleMedia.h"

#ifdef LINUX
#include <SDL2/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif

#include <iostream>

namespace sgl
{
namespace media
{

void ModuleMedia::PrintBuildLibs()
{
    SDL_version mixVer;
    SDL_MIXER_VERSION(&mixVer);

    std::cout << "====== MEDIA - BUILD LIBRARIES ======" << std::endl;
    std::cout << "SDL_mixer version: "
              << static_cast<int>(mixVer.major) << "."
              << static_cast<int>(mixVer.minor) << "."
              << static_cast<int>(mixVer.patch) << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

void ModuleMedia::PrintRuntimeLibs()
{
    const SDL_version * mixVer = Mix_Linked_Version();

    std::cout << "======  MEDIA - RUNTIME LIBRARIES ======" << std::endl;
    std::cout << "SDL_mixer version: "
              << static_cast<int>(mixVer->major) << "."
              << static_cast<int>(mixVer->minor) << "."
              << static_cast<int>(mixVer->patch) << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

} // namespace media
} // namespace sgl
