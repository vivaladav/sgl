#include "sgl/graphic/ParticlesUpdater.h"

#include "sgl/graphic/Particle.h"

namespace sgl
{
namespace graphic
{

ParticlesUpdater::~ParticlesUpdater()
{
    for(auto p : mParticles)
        delete p;

    for(auto p : mDelayedParticles)
        delete p;

    for(auto p : mActiveParticles)
        delete p;
}

void ParticlesUpdater::AddParticle(const ParticleData & initData)
{
    Particle * p = CreateParticle(initData);
    p->ClearDone();

    if(p->HasDelay())
        mDelayedParticles.emplace_back(p);
    else
        mActiveParticles.emplace_back(p);
}

void ParticlesUpdater::Update(float delta)
{
    // DELAYED PARTICLES
    auto itD = mDelayedParticles.begin();

    while(itD != mDelayedParticles.end())
    {
        auto p = *itD;

        p->SetDelay(p->GetDelay() - delta);

        if(!p->HasDelay())
        {
            p->SetDelay(0.f);
            mActiveParticles.emplace_back(p);

            itD = mDelayedParticles.erase(itD);
        }
        else
            ++itD;
    }

    // ACTIVE PARTICLES
    auto itA = mActiveParticles.begin();

    while(itA != mActiveParticles.end())
    {
        auto p = *itA;

        p->Update(delta);

        // particle can be removed
        if(p->IsDone())
        {
            itA = mActiveParticles.erase(itA);
            mParticles.push_back(p);
        }
        else
            ++itA;
    }
}

void ParticlesUpdater::Render()
{
    for(auto p : mActiveParticles)
        p->Render();
}

} // namespace graphic
} // namespace sgl
