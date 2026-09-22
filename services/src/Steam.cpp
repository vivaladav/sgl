#include "sgl/services/Steam.h"

#if USE_STEAM
#include <steam/steam_api.h>

#include <string>
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
    if(mInitDone)
        return SteamUtils()->GetAppID();
    else
        return false;
}

const char * Steam::GetAppLanguage()
{
    if(mInitDone)
        return SteamApps()->GetCurrentGameLanguage();
    else
        return nullptr;
}

// -- SYSTEM INFO --
bool Steam::IsRunningOnDeck()
{
    if(mInitDone)
        return SteamUtils()->IsRunningOnSteamHardware() == k_ESteamHardwareTypeSteamDeck;
    else
        return false;
}

// -- USER INFO --
unsigned int Steam::GetUserId()
{
    if(mInitDone)
        return SteamUser()->GetSteamID().GetAccountID();
    else
        return 0;
}

const char * Steam::GetUserName()
{
    if(mInitDone)
        return SteamFriends()->GetPersonaName();
    else
        return nullptr;
}

// -- STATS --
bool Steam::GetStat(const char * name, int * value)
{
    if(mInitDone)
        return SteamUserStats()->GetStat(name, value);
    else
        return false;
}

bool Steam::GetStat(const char * name, float * value)
{
    if(mInitDone)
        return SteamUserStats()->GetStat(name, value);
    else
        return false;
}

bool Steam::SetStat(const char * name, int value)
{
    if(mInitDone)
        return SteamUserStats()->SetStat(name, value);
    else
        return false;
}

bool Steam::SetStat(const char * name, float value)
{
    if(mInitDone)
        return SteamUserStats()->SetStat(name, value);
    else
        return false;
}

bool Steam::UpdateAverageStat(const char * name, float value, double sessionLen)
{
    if(mInitDone)
        return SteamUserStats()->UpdateAvgRateStat(name, value, sessionLen);
    else
        return false;
}

bool Steam::ResetStats()
{
    if(mInitDone)
        return SteamUserStats()->ResetAllStats(false);
    else
        return false;
}

// -- ACHIEVEMENTS --
bool Steam::ClearAchievement(const char * name)
{
    if(mInitDone)
        return SteamUserStats()->ClearAchievement(name);
    else
        return false;
}

bool Steam::IsAchievementHidden(const char * name)
{
    if(!mInitDone)
        return false;

    const std::string ok("1");

    const char * key = "hidden";
    const std::string res = SteamUserStats()->GetAchievementDisplayAttribute(name, key);

    return !res.empty() && res == ok;
}

bool Steam::IsAchievementUnlocked(const char * name, bool * unlocked)
{
    if(mInitDone)
        return SteamUserStats()->GetAchievement(name, unlocked);
    else
        return false;
}

unsigned int Steam::GetNumberOfAchievements()
{
    if(mInitDone)
        return SteamUserStats()->GetNumAchievements();
    else
        return 0;
}

bool Steam::ShowAchievementProgressNotification(const char * name, unsigned int progress,
                                                unsigned int max)
{
    if(mInitDone)
        return SteamUserStats()->IndicateAchievementProgress(name, progress, max);
    else
        return false;
}

bool Steam::UnlockAchievement(const char * name)
{
    if(mInitDone)
        return SteamUserStats()->SetAchievement(name);
    else
        return false;
}

bool Steam::ResetStatsAndAchievements()
{
    if(mInitDone)
        return SteamUserStats()->ResetAllStats(true);
    else
        return false;
}

bool Steam::StoreStatsAndAchievements()
{
    if(mInitDone)
        return SteamUserStats()->StoreStats();
    else
        return false;
}

// ===== NOT USING THE STEAM SDK =====
#else
bool Steam::NeedRestartInSteam(unsigned int) { return false; }
bool Steam::Init() { return false; }
void Steam::Shutdown() { }
unsigned int Steam::GetAppId() { return 0; }
const char * Steam::GetAppLanguage() { return nullptr; }
bool Steam::IsRunningOnDeck() { return false; }
unsigned int Steam::GetUserId() { return 0; }
const char * Steam::GetUserName() { return nullptr; }
bool Steam::GetStat(const char * name, int * value) { return false; }
bool Steam::GetStat(const char * name, float * value) { return false; }
bool Steam::SetStat(const char * name, int value) { return false; }
bool Steam::SetStat(const char * name, float value) { return false; }
bool Steam::UpdateAverageStat(const char * name, float value, double sessionLen) { return false; }
bool Steam::ResetStats() { return false; }
bool Steam::ClearAchievement(const char * name) { return false; }
bool Steam::IsAchievementHidden(const char * name) { return false; }
bool Steam::IsAchievementUnlocked(const char * name, bool * unlocked)  { return false; }
unsigned int Steam::GetNumberOfAchievements() { return 0; }
bool Steam::ShowAchievementProgressNotification(const char * name, unsigned int progress,
                                                unsigned int max) { return false; }
bool Steam::UnlockAchievement(const char * name) { return false; }
bool Steam::ResetStatsAndAchievements() { return false; }
bool Steam::StoreStatsAndAchievements() { return false; }
#endif

} // namespace services
} // namespace sgl