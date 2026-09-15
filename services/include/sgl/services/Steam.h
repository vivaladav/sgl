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

    bool NeedRestartInSteam(unsigned int appID);

    bool Init();
    void Shutdown();

    const char * GetLanguage();

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

} // namespace services
} // namespace sgl
