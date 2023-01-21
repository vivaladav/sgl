#include "sgl/core/Timer.h"

#include "TimerManager.h"

namespace sgl
{
namespace core
{

Timer::~Timer()
{
    Stop();
}

unsigned int Timer::AddTimeoutFunction(const std::function<void()> & f)
{
    static unsigned int num = 0;

    int fId = ++num;
    mOnTimeout.emplace(fId, f);

    return fId;
}

void Timer::RemoveTimeoutFunction(unsigned int fId)
{
    auto it = mOnTimeout.find(fId);

    if(it != mOnTimeout.end())
        mOnTimeout.erase(it);
}

void Timer::Start()
{
    TimerManager::Instance()->AddTimer(this);

    mRunning = true;

    mT0 = std::chrono::high_resolution_clock::now();
}

void Timer::Stop()
{
    if(!mRunning)
        return ;

    TimerManager::Instance()->RemoveTimer(this);

    mRunning = false;
}

void Timer::Update()
{
    const float minDelta = 0.01f;

    const auto t1 = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<float> elapsed = t1 - mT0;
    const float d = mTimeoutTime - elapsed.count();

    if(d > minDelta)
        return ;

    // execute callbacks
    for(auto & it: mOnTimeout)
        it.second();

    // stop updates if single shot
    if(mSingleShot)
        Stop();

    // reset time
    mT0 = t1;
}

} // namespace core
} // namespace sgl
