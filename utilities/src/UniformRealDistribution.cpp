#include "sgl/utilities/UniformRealDistribution.h"

#include <chrono>

namespace sgl
{
namespace utilities
{

UniformRealDistribution::UniformRealDistribution(float min, float max, unsigned int seed)
{
    if(SEED_RANDOM == seed)
        mGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    else
        mGenerator.seed(seed);

    mDistribution.param(std::uniform_real_distribution<float>::param_type(min, max));
}

} // namespace utilities
} // namespace sgl
