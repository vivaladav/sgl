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
// -- INIT / SHUTDOWN --
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
// -- APP INFO --
unsigned int Steam::GetAppId()
{
    return SteamUtils()->GetAppID();
}

const char * Steam::GetAppLanguage()
{
    return SteamApps()->GetCurrentGameLanguage();
}

// -- SYSTEM INFO --
bool Steam::IsRunningOnDeck()
{
    return SteamUtils()->IsRunningOnSteamHardware() == k_ESteamHardwareTypeSteamDeck;
}

// -- USER INFO --
unsigned int Steam::GetUserId()
{
    return SteamUser()->GetSteamID().GetAccountID();
}

const char * Steam::GetUserName()
{
    return SteamFriends()->GetPersonaName();
}
// ===== NOT USING THE STEAM SDK =====
#else
bool Steam::NeedRestartInSteam(unsigned int appID) { return false; }
bool Steam::Init() { return false; }
void Steam::Shutdown() { }
unsigned int Steam::GetAppId() { return 0; }
const char * Steam::GetAppLanguage() { return nullptr; }
bool Steam::IsRunningOnDeck() { return false; }
unsigned int Steam::GetUserId() { return 0; }
const char * Steam::GetUserName() { return nullptr; }
#endif


} // namespace services
} // namespace sgl