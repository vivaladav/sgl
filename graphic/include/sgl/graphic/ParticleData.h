#pragma once

namespace sgl
{
namespace graphic
{

class Texture;

struct ParticleData
{
    ParticleData(float x, float y, float s)
        : x0(x)
        , y0(y)
        , speed(s)
    {
    }

    float x0 = 0.f;
    float y0 = 0.f;
    float speed = 0.f;
};

struct TexturedParticleData : public ParticleData
{
    TexturedParticleData(float x, float y, float s, Texture * t)
        : ParticleData(x, y, s)
        , tex(t)
    {
    }

    Texture * tex;
};

} // namespace graphic
} // namespace sgl
