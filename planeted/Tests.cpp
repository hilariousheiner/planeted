#include "Tests.h"

#include <fstream>

#include "PixelMap.h"
#include "PPM.h"

namespace Planeted
{
    static Random::NoiseFunction1D zeroFun1D = [](const float &p, const Random::NoiseParameters&)   { return 0.0f; };
    static Random::NoiseFunction2D zeroFun2D = [](const Vector2 &p, const Random::NoiseParameters&) { return 0.0f; };
    static Random::NoiseFunction3D zeroFun3D = [](const Vector3 &p, const Random::NoiseParameters&) { return 0.0f; };

    static std::uint8_t NoiseToGrayScale(float noise)
    {
        return ToUint8(SignedToUnitRange(noise));
    }

    static ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction1D noiseFun)
    {
        return [fbmParams, noiseParams, noiseFun](const int x, const int y)
        {
            float nx = x/512.0f -0.5f;
            return NoiseToGrayScale(Random::FBM1D(nx, fbmParams, noiseParams, noiseFun));
        };
    }
    static ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction2D noiseFun)
    {
        return [fbmParams, noiseParams, noiseFun](const int x, const int y)
        {
            float nx = x/512.0f -0.5f;
            float ny = y/512.0f -0.5f;
            return NoiseToGrayScale(Random::FBM2D({nx, ny}, fbmParams, noiseParams, noiseFun));
        };
    }
    static ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction3D noiseFun)
    {
        return [fbmParams, noiseParams, noiseFun](const int x, const int y)
        {
            float nx = x/512.0f -0.5f;
            float ny = y/512.0f -0.5f;
            return NoiseToGrayScale(Random::FBM3D({nx, ny, 1.0f}, fbmParams, noiseParams, noiseFun));
        };
    }

    static void noiseTest(const std::string &filename, ColorFunction fn)
    {
        PixelMap pixMap = PixelMap(512, 512);

        pixMap.FillRect(0, 0, 512, 512, fn);

        std::ofstream ppmfile(filename + ".ppm");

        ppmfile << PPM::PixelMapToPPM(pixMap);
    }

    void NoiseTest1D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle)
    {
        Random::NoiseFunction1D noiseFun = Random::GetNoiseFunction1D(noiseType, noiseStyle);
        if(noiseFun == nullptr)
        {
            noiseFun = zeroFun1D;
        }

        ColorFunction fn = ToColorFunction(fbmParams, noiseParams, noiseFun);

        noiseTest(filename, fn);
    }
    void NoiseTest2D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle)
    {
        Random::NoiseFunction2D noiseFun = Random::GetNoiseFunction2D(noiseType, noiseStyle);
        if(noiseFun == nullptr)
        {
            noiseFun = zeroFun2D;
        }

        ColorFunction fn = ToColorFunction(fbmParams, noiseParams, noiseFun);

        noiseTest(filename, fn);
    }
    void NoiseTest3D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseTypeEnum noiseType, Random::NoiseStyleEnum noiseStyle)
    {
        Random::NoiseFunction3D noiseFun = zeroFun3D;

        noiseFun = Random::GetNoiseFunction3D(noiseType, noiseStyle);
        if(noiseFun == nullptr)
        {
            noiseFun = zeroFun3D;
        }

        ColorFunction fn = ToColorFunction(fbmParams, noiseParams, noiseFun);

        noiseTest(filename, fn);
    }
}
