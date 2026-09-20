#pragma once

namespace sgl
{
namespace services
{

class Steam
{
public:
    static Steam * Create();
    static Steam * Instance();
    static void Destroy();

    // -- INIT / SHUTDOWN --
    bool NeedRestartInSteam(unsigned int appID);
    bool Init();
    bool IsInitDone() const;
    void Shutdown();

    // -- APP INFO --
    unsigned int GetAppId();
    const char * GetAppLanguage();

    // -- SYSTEM INFO --
    bool IsRunningOnDeck();

    // -- USER INFO --
    unsigned int GetUserId();
    const char * GetUserName();

    // -- STATS --
    bool GetStat(const char * name, int * value);
    bool GetStat(const char * name, float * value);
    bool SetStat(const char * name, int value);
    bool SetStat(const char * name, float value);
    bool UpdateAverageStat(const char * name, float value, double sessionLen);
    bool ResetStats();

    // -- ACHIEVEMENTS --
    bool ClearAchievement(const char * name);
    bool IsAchievementHidden(const char * name);
    bool IsAchievementUnlocked(const char * name, bool * unlocked);
    unsigned int GetNumberOfAchievements();
    bool UnlockAchievement(const char * name);

    bool ResetStatsAndAchievements();
    bool StoreStatsAndAchievements();

private:
    Steam();
    ~Steam();

private:
    static Steam * mInstance;

    bool mInitDone = false;
};

inline Steam::Steam() : mInitDone(false) { }
inline Steam::~Steam() { Shutdown(); }

inline Steam * Steam::Instance() { return mInstance; }

inline bool Steam::IsInitDone() const { return mInitDone; }

} // namespace services
} // namespace sgl
