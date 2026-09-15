#include "sgl/services/Steam.h"

#if USE_STEAM
#include <steam/steam_api.h>
#endif

namespace sgl
{
namespace services
{
Steam * Steam::mInstance = nullptr;

Steam * Steam::Create()
{
    if(!mInstance)
        mInstance = new Steam;

    return mInstance;
}

void Steam::Destroy()
{
    delete mInstance;
    mInstance = nullptr;
}

// ===== USING THE STEAM SDK =====
#ifdef USE_STEAM
bool Steam::NeedRestartInSteam(unsigned int appID)
{
    return SteamAPI_RestartAppIfNecessary(appID);
}

bool Steam::Init()
{
    mInitDone = SteamAPI_Init();

    return mInitDone;
}

void Steam::Shutdown()
{
    SteamAPI_Shutdown();
}

const char * Steam::GetLanguage()
{
    return SteamApps()->GetCurrentGameLanguage();
}
// ===== NOT USING THE STEAM SDK =====
#else
bool Steam::NeedRestartInSteam(unsigned int appID) { return false; }

bool Steam::Init() { return false; }

void Steam::Shutdown() { }

const char * Steam::GetLanguage() { return nullptr; }
#endif


} // namespace services
} // namespace sgl