#include "sgl/graphic/ParticlesManager.h"

#include "sgl/graphic/ParticlesUpdater.h"

namespace sgl
{
namespace graphic
{

ParticlesManager::~ParticlesManager()
{
    for(auto it : mUpdaters)
        delete it.second;
}

ParticlesUpdater * ParticlesManager::GetUpdater(unsigned int key)
{
    auto res = mUpdaters.find(key);

    if(res != mUpdaters.end())
        return res->second;
    else
        return nullptr;
}

void ParticlesManager::Update(float delta)
{
    for(auto it : mUpdaters)
        it.second->Update(delta);
}

void ParticlesManager::Render()
{
    for(auto it : mUpdaters)
        it.second->Render();
}

} // namespace graphic
} // namespace sgl
