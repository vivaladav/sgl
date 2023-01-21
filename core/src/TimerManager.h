#pragma once

#include <vector>

namespace sgl
{
namespace core
{

class Timer;

class TimerManager
{
public:
    static TimerManager * Create();
    static TimerManager * Instance();
    static void Destroy();

    void AddTimer(Timer * t);
    void RemoveTimer(Timer * t);

    void Update();

private:
    TimerManager() = default;
    ~TimerManager() = default;

private:
    static TimerManager * mInstance;

    std::vector<Timer *> mTimers;
    std::vector<Timer *> mTimersToRemove;
};

inline TimerManager * TimerManager::Instance() { return mInstance; }

inline void TimerManager::AddTimer(Timer * t) { mTimers.push_back(t); }
inline void TimerManager::RemoveTimer(Timer * t) { mTimersToRemove.push_back(t); }

} // namespace core
} // namespace sgl
