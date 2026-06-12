#ifndef PLANETED_TESTS_H
#define PLANETED_TESTS_H

#include "Random.h"

namespace Planeted
{
    void NoiseTest1D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle);
    void NoiseTest2D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle);
    void NoiseTest3D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle);
}
#endif
