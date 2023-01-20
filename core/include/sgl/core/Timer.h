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
    Timer(float sec);
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

    float mTimeoutTime = 0.f;
    float mTime = 0.f;

    bool mSingleShot = false;
};

inline Timer::Timer(float sec) : mTimeoutTime(sec)
{
}

inline bool Timer::IsSingleShot() const { return mSingleShot; }
inline void Timer::SetSingleShot(bool val) { mSingleShot = val; }

} // namespace core
} // namespace sgl
