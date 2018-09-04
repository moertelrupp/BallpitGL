#include "ECSComponent.hpp"

namespace upp
{
    uint BaseECSComponent::registerComponentType(const ComponentType& component)
    {
        if (componentTypes == nullptr) {
            componentTypes = new Array<ComponentType>();
        }
        uint index = componentTypes->size();
        componentTypes->push_back(component);
        return index;
    }

    ECSComponentCreateFunction BaseECSComponent::getComponentCreateFunction(uint ID)
    {
        return (*componentTypes)[ID].createFn;
    }

    ECSComponentFreeFunction BaseECSComponent::getComponentFreeFunction(uint ID)
    {
        return (*componentTypes)[ID].freeFn;
    }

    size_t BaseECSComponent::getComponentSize(uint ID)
    {
        return (*componentTypes)[ID].size;
    }

    ComponentType& BaseECSComponent::getComponentType(uint ID)
    {
        return (*componentTypes)[ID];
    }

    bool BaseECSComponent::isTypeValid(uint id)
    {
        return id < (*componentTypes).size();
    }

    Array<ComponentType>* BaseECSComponent::componentTypes;
}