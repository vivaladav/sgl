#pragma once

#include <functional>
#include <map>

namespace sgl
{
namespace core
{

class Timer
{
public:
    Timer(int ms);
    ~Timer();

    bool IsSingleShot() const;
    void SetSingleShot(bool val);

    unsigned int AddTimeoutFunction(const std::function<void()> & f);
    void RemoveTimeoutFunction(unsigned int fId);

    void Start();
    void Stop();

    void Update(float delta);

private:
    std::map<unsigned int, std::function<void()>> mOnTimeout;

    int mTimeoutTime = 0;
    int mTime = 0;

    bool mSingleShot = false;
};

inline Timer::Timer(int ms) : mTimeoutTime(ms)
{
}

inline bool Timer::IsSingleShot() const { return mSingleShot; }
inline void Timer::SetSingleShot(bool val) { mSingleShot = val; }

} // namespace core
} // namespace sgl
