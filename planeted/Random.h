#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <random>

namespace Planeted
{
    class Random
    {
    public:
        Random()
            : engine(std::random_device{}()),
              distribution(0.0f, 1.0f)
        { }

        float GetValue()
        {
            return this->distribution(this->engine);
        }

    private:
        std::mt19937 engine;
        std::uniform_real_distribution<float> distribution;
    };
}

#endif // PLANETED_RANDOM_H
