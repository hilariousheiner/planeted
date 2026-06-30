#include "Tests.h"

#include <fstream>

#include "PixelMap.h"
#include "PPM.h"
#include "PGM.h"

namespace Planeted
{
    static uint16_t sample_size = 256;

    static std::uint8_t NoiseToGrayScale(float noise)
    {
        return ToUint8(SignedToUnitRange(noise));
    }

    static ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction1D noiseFun)
    {
        return [fbmParams, noiseParams, noiseFun](const int x, const int y)
        {
            float nx = x/static_cast<float>(sample_size) - 0.5f;
            return NoiseToGrayScale(Random::FBM1D(nx, fbmParams, noiseParams, noiseFun));
        };
    }
    static ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction2D noiseFun)
    {
        return [fbmParams, noiseParams, noiseFun](const int x, const int y)
        {
            float nx = x/static_cast<float>(sample_size) - 0.5f;
            float ny = y/static_cast<float>(sample_size) - 0.5f;
            return NoiseToGrayScale(Random::FBM2D({nx, ny}, fbmParams, noiseParams, noiseFun));
        };
    }
    static ColorFunction ToColorFunction(Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction3D noiseFun)
    {
        return [fbmParams, noiseParams, noiseFun](const int x, const int y)
        {
            float nx = x/static_cast<float>(sample_size) - 0.5f;
            float ny = y/static_cast<float>(sample_size) - 0.5f;
            return NoiseToGrayScale(Random::FBM3D({nx, ny, 1.0f}, fbmParams, noiseParams, noiseFun));
        };
    }

    static void noiseTest(const std::string &filename, ColorFunction fn)
    {
        PixelMap pixMap = PixelMap(sample_size, sample_size);

        pixMap.FillRect(0, 0, sample_size, sample_size, fn);

        std::ofstream pgmfile(filename + ".pgm");

        pgmfile << PGM::PixelMapToPGM(pixMap);
    }

    void NoiseTest1D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction1D noiseFun)
    {
        ColorFunction fn = ToColorFunction(fbmParams, noiseParams, noiseFun);
        noiseTest(filename, fn);
    }
    void NoiseTest2D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction2D noiseFun)
    {
        ColorFunction fn = ToColorFunction(fbmParams, noiseParams, noiseFun);
        noiseTest(filename, fn);
    }
    void NoiseTest3D(const std::string &filename, Random::FBMParameters &fbmParams, Random::NoiseParameters &noiseParams, Random::NoiseFunction3D noiseFun)
    {
        ColorFunction fn = ToColorFunction(fbmParams, noiseParams, noiseFun);
        noiseTest(filename, fn);
    }
}
