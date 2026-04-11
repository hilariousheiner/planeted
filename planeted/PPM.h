#ifndef PLANETED_PPM_H
#define PLANETED_PPM_H

#include <sstream>
#include <string.h>
#include <vector>

#include "PixelMap.h"

namespace Planeted
{
    namespace PPM
    {
        std::string PixelMapToPPM(const PixelMap &pmap);
    }
}
#endif // PLANETED_PPM_H
