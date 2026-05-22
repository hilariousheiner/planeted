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
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::WhiteNoise(x*100))); };
            break;
        case Random::NoiseTypeEnum::Value:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::ValueNoise(x * 0.05f))); };
            break;
        case Random::NoiseTypeEnum::Perlin:
            break;
        case Random::NoiseTypeEnum::Gradient:
            fn = [](const int x, const int y) { return ToUint8(SignedToUnitRange(Random::GradientNoise(x * 0.05f))); };
            break;
        default:
            break;
        }
        noiseTest("1D", "noiseTest1D.ppm", fn);
    }
}
#endif
