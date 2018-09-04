#include "Timer.hpp"

namespace upp
{
    double Timer::getTime()
    {
        return glfwGetTime();
    }
}

