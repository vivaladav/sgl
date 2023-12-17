#pragma once

namespace sgl
{
namespace graphic
{

class Texture;

struct ParticleData
{
    ParticleData() : tex(nullptr) {}
    ParticleData(Texture * t) : tex(t) {}

    Texture * tex;
};

} // namespace graphic
} // namespace sgl
