#include "sgl/utilities/StateManager.h"

#include "sgl/utilities/State.h"

#include <iostream>

namespace sgl
{
namespace utilities
{

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
    mActive = nullptr;

    for(auto & s : mStates)
        delete s.second;
}

bool StateManager::AddState(State * state)
{
    // no state
    if(!state)
        return false;

    const unsigned int stateId = state->GetStateId();

    auto res = mStates.find(stateId);

    // state is already registered
    if(res != mStates.end())
    {
        std::cerr << "StateManager::AddState - STATE " << stateId << " ALREADY ADDED" << std::endl;
        return false;
    }

    // add state
    state->mManager = this;
    mStates.emplace(stateId, state);

    return true;
}

State * StateManager::RemoveState(int stateId)
{
    auto res = mStates.find(stateId);

    if(res != mStates.end())
    {
        mStates.erase(res);

        return res->second;
    }

    return nullptr;
}

void StateManager::RemoveAndDestroyState(int stateId)
{
    State * res = RemoveState(stateId);
    delete res;
}

bool StateManager::RequestNextActiveState(int stateId)
{
    // need to use SetInitialActiveState first
    if(mInit)
        return false;

    auto res = mStates.find(stateId);

    // state not found
    if(res == mStates.end())
        return false;

    // requesting same state as already active
    if(res->second == mActive)
        return false;

    // schedule state to be next active
    mNext = res->second;

    mUpdated = false;

    return true;
}

bool StateManager::SetInitialActiveState(int stateId)
{
    // initial state already set once
    if(mActive != nullptr || mNext != nullptr)
        return false;

    auto res = mStates.find(stateId);

    // state not found
    if(res == mStates.end())
        return false;

    mNext = res->second;

    return true;
}

int StateManager::GetActiveStateId() const
{
    if(mActive != nullptr)
        return mActive->GetStateId();
    else
        return -1;
}

void StateManager::Update(float delta)
{
    UpdateActive();

    mActive->Update(delta);

    mUpdated = true;
}

void StateManager::UpdateActive()
{
    if(mNext != nullptr)
    {
        // change happening after SetInitialActiveState
        if(mInit)
            mInit = false;
        // change happening after RequestNextActiveState
        else
        {
            // skip change if the current active state has not been updated yet
            // this is required because some UI events can trigger changes before the update
            if(!mUpdated)
                return ;

            if(mActive)
                mActive->OnInactive();
        }

        mActive = mNext;
        mNext = nullptr;
    }
    else
        return ;

    mActive->OnActive();
}

} // namespace utilities
} // namespace sgl
