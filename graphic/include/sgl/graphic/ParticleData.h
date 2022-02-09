#pragma once

namespace sgl
{
namespace graphic
{

class Texture;

struct ParticleData
{
    ParticleData(Texture * t) : tex(t) {}

    Texture * tex = nullptr;
};

} // namespace graphic
} // namespace sgl
