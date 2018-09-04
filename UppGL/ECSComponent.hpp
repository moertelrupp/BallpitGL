#pragma once

#include "UppIncludes.hpp"

namespace upp
{
    struct ComponentType
    {
        ComponentType(ECSComponentCreateFunction createFn,
            ECSComponentFreeFunction freeFn, size_t size)
            : createFn(createFn), freeFn(freeFn), size(size) {}

        ECSComponentCreateFunction createFn;
        ECSComponentFreeFunction freeFn;
        size_t size;
    };

    struct BaseECSComponent
    {
        EntityHandle entity = NULL_ENTITY_HANDLE;
        static uint registerComponentType(const ComponentType& component);
        static ECSComponentCreateFunction getComponentCreateFunction(uint ID);
        static ECSComponentFreeFunction getComponentFreeFunction(uint ID);
        static size_t getComponentSize(uint ID);
        static ComponentType& getComponentType(uint ID);
        static bool isTypeValid(uint id);

    private:
        static Array<ComponentType>* componentTypes;
    };

    template<typename Component>
    struct ECSComponent : public BaseECSComponent
    {
        static ECSComponentCreateFunction CREATE_FUNCTION;
        static ECSComponentFreeFunction FREE_FUNCTION;
        static const uint ID;
        static const size_t SIZE;
    };

    template<typename Component>
    uint ECSComponentCreate(Array<byte>& memory, EntityHandle handle, BaseECSComponent* comp)
    {
        // Resize memory to fit in Component
        uint index = memory.size();
        memory.resize(index + Component::SIZE);
        // Create new Component with copy constructor
        Component* component = new(&memory[index]) Component(*((Component*)comp));
        component->entity = handle;
        return index;
    }

    template<typename Component>
    void ECSComponentFree(BaseECSComponent* comp) {
        Component* component = (Component*)comp;
        component->~Component();
    }

    template<typename Component>
    ECSComponentCreateFunction ECSComponent<Component>::CREATE_FUNCTION = &ECSComponentCreate<Component>;

    template<typename Component>
    ECSComponentFreeFunction ECSComponent<Component>::FREE_FUNCTION = &ECSComponentFree<Component>;

    template<typename Component>
    const uint ECSComponent<Component>::ID = 
        BaseECSComponent::registerComponentType(ComponentType(&ECSComponentCreate<Component>, &ECSComponentFree<Component>, sizeof(Component)));

    template<typename Component>
    const size_t ECSComponent<Component>::SIZE = sizeof(Component);
}