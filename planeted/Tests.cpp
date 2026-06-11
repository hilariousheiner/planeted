#include "Tests.h"

namespace Planeted
{
    std::uint8_t NoiseToGrayScale(float noise)
    {
        return ToUint8(SignedToUnitRange(noise));
    }

    ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction1D noiseFun)
    {
        return [fbmParams, noiseParams, noiseFun](const int x, const int y)
        {
            float nx = x/512.0f -0.5f;
            return NoiseToGrayScale(Random::FBM1D(nx, fbmParams, noiseParams, noiseFun));
        };
    }
    ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction2D noiseFun)
    {
        return [fbmParams, noiseParams, noiseFun](const int x, const int y)
        {
            float nx = x/512.0f -0.5f;
            float ny = y/512.0f -0.5f;
            return NoiseToGrayScale(Random::FBM2D({nx, ny}, fbmParams, noiseParams, noiseFun));
        };
    }
    ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction3D noiseFun)
    {
        return [fbmParams, noiseParams, noiseFun](const int x, const int y)
        {
            float nx = x/512.0f -0.5f;
            float ny = y/512.0f -0.5f;
            return NoiseToGrayScale(Random::FBM3D({nx, ny, 1.0f}, fbmParams, noiseParams, noiseFun));
        };
    }

    void noiseTest(const std::string &name, const std::string &filename, ColorFunction fn)
    {
        std::cout << "running " << name << " noise test." << std::endl;

        PixelMap pixMap = PixelMap(512, 512);

        pixMap.FillRect(0, 0, 512, 512, fn);

        std::ofstream ppmfile(filename);

        ppmfile << PPM::PixelMapToPPM(pixMap);
        std::cout << "done." << std::endl;
    }

    void NoiseTest1D(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle)
    {
        Random::NoiseFunction1D noiseFun = Random::GetNoiseFunction1D(noiseType, noiseStyle);
        if(noiseFun == nullptr)
        {
            noiseFun = zeroFun1D;
        }

        ColorFunction fn = ToColorFunction(fbmParams, noiseParams, noiseFun);

        noiseTest("Noise 1D", "noiseTest1D.ppm", fn);
    }
    void NoiseTest2D(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle)
    {
        Random::NoiseFunction2D noiseFun = Random::GetNoiseFunction2D(noiseType, noiseStyle);
        if(noiseFun == nullptr)
        {
            noiseFun = zeroFun2D;
        }

        ColorFunction fn = ToColorFunction(fbmParams, noiseParams, noiseFun);

        noiseTest("Noise 2D", "noiseTest2D.ppm", fn);
    }
    void NoiseTest3D(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle)
    {
        Random::NoiseFunction3D noiseFun = zeroFun3D;

        noiseFun = Random::GetNoiseFunction3D(noiseType, noiseStyle);
        if(noiseFun == nullptr)
        {
            noiseFun = zeroFun3D;
        }

        ColorFunction fn = ToColorFunction(fbmParams, noiseParams, noiseFun);

        noiseTest("Noise 3D", "noiseTest3D.ppm", fn);
    }
}
