#include "PPM.h"

namespace Planeted
{
    namespace PPM
    {
        std::string PixelMapToPPM(const PixelMap &pmap)
        {
            std::stringstream stream;

            int width = pmap.GetWidth();
            int height = pmap.GetHeight();
            const std::vector<Color>& data = pmap.GetData();

            stream << "P3\n";
            stream << width << " " << height << "\n";
            stream << "255\n";

            for (const Color &pixel : data)
            {
                stream << static_cast<int>(pixel.R) << " ";
                stream << static_cast<int>(pixel.G) << " ";
                stream << static_cast<int>(pixel.B) << "\n";
            }
            return stream.str();
        }
    }
}
