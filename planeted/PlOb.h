#ifndef PLANETED_PLOB_H
#define PLANETED_PLOB_H

/*
 * PlOb = planeted object
 */

#include "Mesh.h"

namespace Planeted
{
    class PlOb
    {
    public:
        virtual Mesh GenerateMesh() = 0;
    };
}
#endif // PLANETED_PLOB_H
