#include "PGM.h"

namespace Planeted
{
    namespace PGM
    {
        std::string PixelMapToPGM(const PixelMap &pmap)
        {
            std::stringstream stream;

            int width = pmap.GetWidth();
            int height = pmap.GetHeight();
            const std::vector<Color>& data = pmap.GetData();

            stream << "P2\n";
            stream << width << " " << height << "\n";
            stream << "255\n";

            for (const Color &pixel : data)
            {
                stream << static_cast<int>(pixel.R) << "\n";
            }
            return stream.str();
        }
    }
}
