#ifndef PLANETED_PBM_H
#define PLANETED_PBM_H

#include <sstream>
#include <string.h>
#include <vector>

#include "PixelMap.h"

namespace Planeted
{
    namespace PGM
    {
        std::string PixelMapToPGM(const PixelMap &pmap);
    }
}
#endif
