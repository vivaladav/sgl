#include "sgl/core/Timer.h"

#include "TimerManager.h"

namespace sgl
{
namespace core
{

Timer::~Timer()
{
    TimerManager::Instance()->RemoveTimer(this);
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
    mTime = mTimeoutTime;

    TimerManager::Instance()->AddTimer(this);
}

void Timer::Stop()
{
    TimerManager::Instance()->RemoveTimer(this);
}

void Timer::Update(float delta)
{
    mTime -= delta;

    const float minDelta = 0.01f;

    // keep going
    if(mTime > minDelta)
        return;

    // execute callbacks
    for(auto & it: mOnTimeout)
        it.second();

    // stop updates if single shot
    if(mSingleShot)
        TimerManager::Instance()->RemoveTimer(this);

    // reset time
    mTime = mTimeoutTime;
}

} // namespace core
} // namespace sgl
