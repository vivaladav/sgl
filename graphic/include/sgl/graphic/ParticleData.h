#pragma once

namespace sgl
{
namespace graphic
{

class Texture;

struct ParticleData
{
    ParticleData(float x, float y, float s, float d)
        : x0(x)
        , y0(y)
        , speed(s)
        , delay(d)
    {
    }

    float x0 = 0.f;
    float y0 = 0.f;
    float speed = 0.f;
    float delay = 0.f;
};

struct TexturedParticleData : public ParticleData
{
    TexturedParticleData(float x, float y, float s, float d, Texture * t)
        : ParticleData(x, y, s, d)
        , tex(t)
    {
    }

    Texture * tex;
};

} // namespace graphic
} // namespace sgl
