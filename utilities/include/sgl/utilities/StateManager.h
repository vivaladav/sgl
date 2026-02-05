#pragma once

#include <unordered_map>

namespace sgl
{
namespace utilities
{

class State;
class StateData;

class StateManager
{
public:
    StateManager();
    ~StateManager();

    bool AddState(State * state);
    State * RemoveState(int stateId);
    void RemoveAndDestroyState(int stateId);
    bool RequestNextActiveState(int stateId, StateData * data = nullptr);
    bool SetInitialActiveState(int stateId, StateData * data = nullptr);

    int GetActiveStateId() const;
    State * GetActiveState() const;

    void Update(float delta);

private:
    void UpdateActive();

private:
    std::unordered_map<int, State *> mStates;

    State * mActive = nullptr;
    State * mNext = nullptr;

    bool mInit = true;
    bool mUpdated = false;
};

inline State * StateManager::GetActiveState() const { return mActive; }

} // namespace utilities
} // namespace sgl
