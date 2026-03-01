#ifndef PLANETED_VECTOR3_H
#define PLANETED_VECTOR3_H

#include <string>

namespace Planeted
{
    class Vector3
    {
        private:
            float x, y, z;

        public:
            Vector3(float x, float y, float z);

            float X();
            float Y();
            float Z();

            Vector3& operator*=(float scalar);

            float Magnitude();
            float SquareMagnitude();
            void Normalize();
    };
}
#endif
