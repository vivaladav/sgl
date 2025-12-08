#pragma once

#include <map>

namespace sgl
{
namespace graphic
{

class ParticlesUpdater;

class ParticlesManager
{
public:
    ~ParticlesManager();

    ParticlesUpdater * GetUpdater(unsigned int key) const;
    void RegisterUpdater(unsigned int key, ParticlesUpdater * updater);
    void UnregisterUpdater(unsigned int key);

    void Update(float delta);
    void Render();

private:
    std::map<unsigned int, ParticlesUpdater *> mUpdaters;
};

inline void ParticlesManager::RegisterUpdater(unsigned int key, ParticlesUpdater * updater)
{
    mUpdaters.emplace(key, updater);
}

inline void ParticlesManager::UnregisterUpdater(unsigned int key)
{
    mUpdaters.erase(key);
}

} // namespace graphic
} // namespace sgl
