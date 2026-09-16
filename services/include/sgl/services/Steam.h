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
