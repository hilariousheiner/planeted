#ifndef PLANETED_TESTS_H
#define PLANETED_TESTS_H

#include <fstream>
#include <iostream>

#include "PixelMap.h"
#include "PPM.h"
#include "Random.h"

namespace Planeted
{
    std::uint8_t NoiseToGrayScale(float noise);

    static ColorFunction defaultColorFunction = [](const int x, const int y) { return 0; };

    static Random::NoiseFunction1D zeroFun1D = [](const float &p, const Random::NoiseParameters&)   { return 0.0f; };
    static Random::NoiseFunction2D zeroFun2D = [](const Vector2 &p, const Random::NoiseParameters&) { return 0.0f; };
    static Random::NoiseFunction3D zeroFun3D = [](const Vector3 &p, const Random::NoiseParameters&) { return 0.0f; };

    ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction1D noiseFun);
    ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction2D noiseFun);
    ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction3D noiseFun);

    void noiseTest(const std::string &name, const std::string &filename, ColorFunction fn);

    void NoiseTest1D(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle);
    void NoiseTest2D(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle);
    void NoiseTest3D(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle);
}
#endif
