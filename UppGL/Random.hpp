#pragma once

#include "UppIncludes.hpp"

namespace upp
{
    class Random
    {
    public:
        static float randomFloat(float min, float max) {
            float result = static_cast<float>(rand() % 1000) / 1000.0f; // Between 0 and 1
            result = result * (max - min) + min;
            return result;
        }
    };
}