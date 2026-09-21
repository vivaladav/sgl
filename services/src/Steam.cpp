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

// -- STATS --
bool Steam::GetStat(const char * name, int * value)
{
    return SteamUserStats()->GetStat(name, value);
}

bool Steam::GetStat(const char * name, float * value)
{
    return SteamUserStats()->GetStat(name, value);
}

bool Steam::SetStat(const char * name, int value)
{
    return SteamUserStats()->SetStat(name, value);
}

bool Steam::SetStat(const char * name, float value)
{
    return SteamUserStats()->SetStat(name, value);
}

bool Steam::UpdateAverageStat(const char * name, float value, double sessionLen)
{
    return SteamUserStats()->UpdateAvgRateStat(name, value, sessionLen);
}

bool Steam::ResetStats()
{
    return SteamUserStats()->ResetAllStats(false);
}

// -- ACHIEVEMENTS --
bool Steam::ClearAchievement(const char * name)
{
    return SteamUserStats()->ClearAchievement(name);
}

bool Steam::IsAchievementHidden(const char * name)
{
    const std::string ok("1");

    const char * key = "hidden";
    const std::string res = SteamUserStats()->GetAchievementDisplayAttribute(name, key);

    return !res.empty() && res == ok;
}

bool Steam::IsAchievementUnlocked(const char * name, bool * unlocked)
{
    return SteamUserStats()->GetAchievement(name, unlocked);
}

unsigned int Steam::GetNumberOfAchievements()
{
    return SteamUserStats()->GetNumAchievements();
}

bool Steam::ShowAchievementProgressNotification(const char * name, unsigned int progress,
                                                unsigned int max)
{
    return SteamUserStats()->IndicateAchievementProgress(name, progress, max);
}

bool Steam::UnlockAchievement(const char * name)
{
    return SteamUserStats()->SetAchievement(name);
}

bool Steam::ResetStatsAndAchievements()
{
    return SteamUserStats()->ResetAllStats(true);
}

bool Steam::StoreStatsAndAchievements()
{
    return SteamUserStats()->StoreStats();
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