#ifndef PLANETED_TESTS_H
#define PLANETED_TESTS_H

#include <fstream>
#include <iostream>

#include "PixelMap.h"
#include "PPM.h"
#include "Random.h"

namespace Planeted
{
    inline std::uint8_t NoiseToGrayScale(float noise)
    {
        return ToUint8(SignedToUnitRange(noise));
    }

    ColorFunction defaultColorFunction = [](const int x, const int y) { return 0; };

    Random::NoiseFunction1D zeroFun1D = [](const float &p)   { return 0.0f; };
    Random::NoiseFunction2D zeroFun2D = [](const Vector2 &p) { return 0.0f; };
    Random::NoiseFunction3D zeroFun3D = [](const Vector3 &p) { return 0.0f; };

    ColorFunction ToColorFunction(Random::NoiseFunction1D noiseFun)
    {
        return [noiseFun](const int x, const int y)
        {
            float nx = x/512.0f -0.5f;
            return NoiseToGrayScale(Random::FBM1D(nx, noiseFun));
        };
    }
    ColorFunction ToColorFunction(Random::NoiseFunction2D noiseFun)
    {
        return [noiseFun](const int x, const int y)
        {
            float nx = x/512.0f -0.5f;
            float ny = y/512.0f -0.5f;
            return NoiseToGrayScale(Random::FBM2D({nx, ny}, noiseFun));
        };
    }
    ColorFunction ToColorFunction(Random::NoiseFunction3D noiseFun)
    {
        return [noiseFun](const int x, const int y)
        {
            float nx = x/512.0f -0.5f;
            float ny = y/512.0f -0.5f;
            return NoiseToGrayScale(Random::FBM3D({nx, ny, 1.0f}, noiseFun));
        };
    }

    inline void noiseTest(const std::string &name, const std::string &filename, ColorFunction fn)
    {
        std::cout << "running " << name << " noise test." << std::endl;

        PixelMap pixMap = PixelMap(512, 512);

        pixMap.FillRect(0, 0, 512, 512, fn);

        std::ofstream ppmfile(filename);

        ppmfile << PPM::PixelMapToPPM(pixMap);
        std::cout << "done." << std::endl;
    }

    inline void NoiseTest1D(Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle)
    {
        Random::NoiseFunction1D noiseFun = Random::GetNoiseFunction1D(noiseType, noiseStyle);
        if(noiseFun == nullptr)
        {
            noiseFun = zeroFun1D;
        }

        ColorFunction fn = ToColorFunction(noiseFun);

        noiseTest("Noise 1D", "noiseTest1D.ppm", fn);
    }
    inline void NoiseTest2D(Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle)
    {
        Random::NoiseFunction2D noiseFun = Random::GetNoiseFunction2D(noiseType, noiseStyle);
        if(noiseFun == nullptr)
        {
            noiseFun = zeroFun2D;
        }

        ColorFunction fn = ToColorFunction(noiseFun);

        noiseTest("Noise 2D", "noiseTest2D.ppm", fn);
    }
    inline void NoiseTest3D(Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle)
    {
        Random::NoiseFunction3D noiseFun = zeroFun3D;

        noiseFun = Random::GetNoiseFunction3D(noiseType, noiseStyle);
        if(noiseFun == nullptr)
        {
            noiseFun = zeroFun3D;
        }

        ColorFunction fn = ToColorFunction(noiseFun);

        noiseTest("Noise 3D", "noiseTest3D.ppm", fn);
    }
}
#endif
