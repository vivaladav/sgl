#pragma once

namespace sgl
{
namespace utilities
{

class StateManager;

class StateData
{
public:
    virtual ~StateData() = default;
};

class State
{
public:
    State(int stateId);
    virtual ~State();

    int GetStateId() const;

    virtual void SetNextStateData(StateData * data);

    virtual void OnActive();
    virtual void OnInactive();

    StateManager * GetStateManager() const;

    virtual void Update(float delta);

private:
    StateManager * mManager = nullptr;

    int mId = 0;

    // manager can set the pointer to itself
    friend class StateManager;
};

inline State::State(int stateId) : mId(stateId) { }
inline State::~State() { }

inline int State::GetStateId() const { return mId; }

inline StateManager * State::GetStateManager() const { return mManager; }

} // namespace utilities
} // namespace sgl
