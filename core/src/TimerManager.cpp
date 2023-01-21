#include "TimerManager.h"

#include "sgl/core/Timer.h"

namespace sgl
{
namespace core
{

TimerManager * TimerManager::mInstance = nullptr;

TimerManager * TimerManager::Create()
{
    if(!mInstance)
        mInstance = new TimerManager;

    return mInstance;
}

void TimerManager::Destroy()
{
    delete mInstance;
    mInstance = nullptr;
}

void TimerManager::Update()
{
    // remove expired timers
    for(auto t : mTimersToRemove)
    {
        for(auto it = mTimers.begin(); it != mTimers.end(); ++it)
        {
            if(*it == t)
            {
                mTimers.erase(it);
                break;
            }

            ++it;
        }
    }

    mTimersToRemove.clear();

    // update timers
    for(Timer * t : mTimers)
        t->Update();
}

} // namespace core
} // namespace sgl
