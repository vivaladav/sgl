#pragma once

// Random number distribution that produces integer values according to a uniform discrete distribution.

#include <random>

namespace sgl
{
namespace utilities
{

class UniformRealDistribution
{
public:
    static const int SEED_RANDOM = 0;

public:
    // values will be generated in the range [min, max]
    UniformRealDistribution(float min, float max, int seed = SEED_RANDOM);

    void SetParameters(float min, float max);

    float GetNextValue();

private:
    std::uniform_real_distribution<float> mDistribution;
    std::mt19937 mGenerator;
};

// ===== INLINE FUNCTIONS =====
inline void UniformRealDistribution::SetParameters(float min, float max)
{
    mDistribution.param(std::uniform_real_distribution<float>::param_type(min, max));
}

inline float UniformRealDistribution::GetNextValue() { return mDistribution(mGenerator); }

} // namespace utilities
} // namespace sgl
