#ifndef PLANETED_FBM_H
#define PLANETED_FBM_H

#include "ValueNoise.h"

namespace Planeted
{
    inline float fbm(const Vector3 &p)
    {
        float G = 0.5f;
        float f = 1.0f;
        float a = 1.0f;
        float t = 0.0f;

        for(int i = 0; i < 4; ++i)
        {
            t += a*ValueNoise::GetValue(p*f);

            f *= 2.0f;
            a *= G;
        }
        return t;
    }
}
#endif // PLANETED_FBM_H
