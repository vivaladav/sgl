#pragma once

#include <chrono>
#include <functional>
#include <map>

namespace sgl
{
namespace core
{

class Timer
{
public:
    Timer(float sec);
    ~Timer();

    bool IsSingleShot() const;
    void SetSingleShot(bool val);

    unsigned int AddTimeoutFunction(const std::function<void()> & f);
    void RemoveTimeoutFunction(unsigned int fId);

    // start or restart the timer
    void Start();
    // stop the timer
    void Stop();
    // continue after stop
    void Resume();

    void Update();

private:
    std::map<unsigned int, std::function<void()>> mOnTimeout;

    std::chrono::time_point<std::chrono::high_resolution_clock> mT0;

    float mTimeoutTime = 0.f;

    bool mSingleShot = false;

    bool mRunning = false;
};

inline Timer::Timer(float sec) : mTimeoutTime(sec)
{
}

inline bool Timer::IsSingleShot() const { return mSingleShot; }
inline void Timer::SetSingleShot(bool val) { mSingleShot = val; }

} // namespace core
} // namespace sgl
