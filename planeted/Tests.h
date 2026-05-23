#ifndef PLANETED_TESTS_H
#define PLANETED_TESTS_H

#include <fstream>
#include <iostream>

#include "PixelMap.h"
#include "PPM.h"
#include "Random.h"

namespace Planeted
{
    inline void noiseTest(const std::string &name, const std::string &filename, ColorFunction fn)
    {
        std::cout << "running " << name << " noise test." << std::endl;

        PixelMap pixMap = PixelMap(512, 512);

        pixMap.FillRect(0, 0, 512, 512, fn);

        std::ofstream ppmfile(filename);

        ppmfile << PPM::PixelMapToPPM(pixMap);
        std::cout << "done." << std::endl;
    }

    inline void NoiseTest1D(Random::NoiseTypeEnum noiseType)
    {
        ColorFunction fn = [](const int x, const int y) { return 0; };

        switch(noiseType)
        {
        case Random::NoiseTypeEnum::White:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::WhiteNoise1D(x*100))); };
            break;
        case Random::NoiseTypeEnum::Value:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::ValueNoise1D(x * 0.05f))); };
            break;
        case Random::NoiseTypeEnum::Perlin:
            break;
        case Random::NoiseTypeEnum::Gradient:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::GradientNoise1D(x * 0.05f))); };
            break;
        default:
            break;
        }
        noiseTest("1D", "noiseTest1D.ppm", fn);
    }

    inline void NoiseTest2D(Random::NoiseTypeEnum noiseType)
    {
        ColorFunction fn = [](const int x, const int y) { return 0; };

        switch(noiseType)
        {
        case Random::NoiseTypeEnum::White:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::WhiteNoise2D({x * 100.0f, y * 100.0f}))); };
            break;
        case Random::NoiseTypeEnum::Value:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::ValueNoise2D({x * 0.05f, y * 0.05f}))); };
            break;
        case Random::NoiseTypeEnum::Perlin:
            break;
        case Random::NoiseTypeEnum::Gradient:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::GradientNoise2D({x * 0.05f, y * 0.05f}))); };
            break;
        default:
            break;
        }
        noiseTest("2D", "noiseTest2D.ppm", fn);
    }

    inline void NoiseTest3D(Random::NoiseTypeEnum noiseType)
    {
        ColorFunction fn = [](const int x, const int y) { return 0; };

        switch(noiseType)
        {
        case Random::NoiseTypeEnum::White:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::WhiteNoise3D({x * 100.0f, y * 100.0f, 1.0f}))); };
            break;
        case Random::NoiseTypeEnum::Value:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::ValueNoise3D({x * 0.05f, y * 0.05f, 1.0f}))); };
            break;
        case Random::NoiseTypeEnum::Perlin:
            break;
        case Random::NoiseTypeEnum::Gradient:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::GradientNoise3D({x * 0.05f, y * 0.05f, 1.0f}))); };
            break;
        default:
            break;
        }
        noiseTest("3D", "noiseTest3D.ppm", fn);
    }
}
#endif
