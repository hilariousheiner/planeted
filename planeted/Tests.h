#ifndef PLANETED_TESTS_H
#define PLANETED_TESTS_H

#include <fstream>
#include <iostream>

#include "PixelMap.h"
#include "PPM.h"
#include "Random.h"

namespace Planeted
{
    inline void NoiseTest()
    {
        /*noise test:*/
        std::cout << "running noise test" << std::endl;

        PixelMap pixMap = PixelMap(512, 512);
        for(int x = 0; x < 512; ++x)
        {
            for(int y = 0; y < 512; ++y)
            {
                //std::uint8_t c = ToUint8(SignedToUnitRange(Random::GradientNoise({x * 0.05f, y * 0.05f, 1.0f})));
                //std::uint8_t c = ToUint8(SignedToUnitRange(Random::GradientNoise(x * 0.05f)));
                std::uint8_t c = ToUint8(SignedToUnitRange(Random::WhiteNoise(x*100)));

                pixMap.PutPixel(x, y, {c, c, c});
            }
        }

        std::ofstream ppmfile("test.ppm");

        ppmfile << PPM::PixelMapToPPM(pixMap);
        std::cout << "done." << std::endl;
        //*/
    }
}

#endif
