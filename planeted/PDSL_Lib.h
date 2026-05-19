#ifndef PLANETED_PDSL_LIB_H
#define PLANETED_PDSL_LIB_H

#include "PDSL.h"

namespace Planeted
{
    namespace PDSL_Lib
    {
        inline void Load(PDSL_Runtime &runtime)
        {
            runtime.InstallBuiltinFunction("icosahedron",
                [](PDSL_Runtime &runtime, const std::vector<Value> &args)
            {
                if(args.size() != 1)
                {
                    throw std::runtime_error("icosahedron expects exactly one argument.");
                }
                return Value(MakeIcosahedron(args[0].ToString()));
            });
        }
    }
}
#endif
