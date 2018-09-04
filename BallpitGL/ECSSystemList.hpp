#pragma once

// Includes
#include "UppIncludes.hpp"
#include "BaseECSSystem.hpp"

namespace upp
{
    class ECSSystemList
    {
    public:
        inline bool addSystem(BaseECSSystem& system)
        {
            if (!system.isValid()) {
                return false;
            }
            systems.push_back(&system);
            return true;
        }

        bool removeSystem(BaseECSSystem& system)
        {
            for (uint i = 0; i < systems.size(); i++) {
                if (&system == systems[i]) {
                    systems.erase(systems.begin() + i);
                    return true;
                }
            }
            return false;
        }

        inline size_t size() {
            return systems.size();
        }

        inline BaseECSSystem* operator[](uint index) {
            return systems[index];
        }

    private:
        Array<BaseECSSystem*> systems;
    };
}