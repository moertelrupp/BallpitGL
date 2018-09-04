#pragma once

// Forward Declarations
namespace upp
{
    class BaseECSComponent;
}

// Includes
#include "UppIncludes.hpp"

namespace upp
{
    class BaseECSSystem
    {
    public:
        enum {
            FLAG_OPTIONAL = 1
        };

        BaseECSSystem() {};

        virtual void preUpdate(float delta) {};
        virtual void updateComponents(float delta, BaseECSComponent** components) = 0;
        virtual void postUpdate(float delta) {};

        const Array<uint>& getComponentTypes(){
            return componentTypes;
        }

        const Array<uint>& getComponentFlags() {
            return componentFlags;
        }

        bool isValid() {
            for (uint i = 0; i < componentFlags.size(); i++) {
                if ((componentFlags[i] & FLAG_OPTIONAL) == 0) {
                    return true;
                }
            }
            return false;
        }

    protected:
        void addComponentType(uint componentType, uint componentFlag = 0)
        {
            componentTypes.push_back(componentType);
            componentFlags.push_back(componentFlag);
        }

    private:
        Array<uint> componentTypes;
        Array<uint> componentFlags;
    };
}