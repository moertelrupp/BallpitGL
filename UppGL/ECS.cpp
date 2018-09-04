#include "ECS.hpp"

namespace upp
{
    ECS::~ECS()
    {
        // Delete Components
        for (Map<uint, Array<byte>>::iterator it = components.begin(); it != components.end(); it++) {
            ComponentType& type = BaseECSComponent::getComponentType(it->first);
            ECSComponentFreeFunction freeFn = type.freeFn;
            Array<byte>& componentMemory = it->second;

            // Loop through components by type size
            for (uint i = 0; i < it->second.size(); i += type.size) {
                freeFn((BaseECSComponent*)(&componentMemory[i]));
            }
        }

        // Delete Entities
        for (uint i = 0; i < entities.size(); i++) {
            delete entities[i];
        }
    }

    EntityHandle ECS::makeEntity(BaseECSComponent** entityComponents, const uint32* componentIDs, uint numComponents)
    {
        // Create new Entity
        entityPtr newEntity = new std::pair<uint, Array<std::pair<uint, uint>>>();
        EntityHandle handle = (EntityHandle)newEntity;
        
        // Add entity Index
        newEntity->first = entities.size();

        // Add entity components
        for (uint i = 0; i < numComponents; i++) {
            // Check if component ID is valid
            if (!BaseECSComponent::isTypeValid(componentIDs[i])) {
                delete newEntity;
                std::cout << "Logger says componentID is invalid!!!" << std::endl;
                return NULL_ENTITY_HANDLE;
            }

            addComponentInternal(handle, componentIDs[i], entityComponents[i]);
        }

        // Add entity
        entities.push_back(newEntity);

        return handle;
    }

    void ECS::removeEntity(EntityHandle handle)
    {
        // Remove Entity components
        Array<std::pair<uint, uint>>& entityComponents = handleToEntityComponents(handle);
        for (uint i = 0; i < entityComponents.size(); i++) {
            deleteComponent(entityComponents[i].first, entityComponents[i].second);
        }

        // Swap last entity with this entity
        uint destIndex = handleToEnityIndex(handle);
        uint srcIndex = entities.size() - 1;
        delete entities[destIndex];
        entities[destIndex] = entities[srcIndex];
        entities[destIndex]->first = destIndex;
        
        // Remove last entity
        entities.pop_back();
    }

    void ECS::deleteComponent(uint componentID, uint memoryIndex)
    {
        // Get Component information
        ComponentType& type = BaseECSComponent::getComponentType(componentID);
        ECSComponentFreeFunction freeFn = type.freeFn;
        size_t typeSize = type.size;

        Array<byte>& memory = components[componentID];
        uint srcIndex = memory.size() - typeSize; // Last Index

        // Get Component Pointers
        BaseECSComponent* destComponent = (BaseECSComponent*)&memory[memoryIndex];
        BaseECSComponent* srcComponent = (BaseECSComponent*)&memory[srcIndex];
        freeFn(destComponent);

        if (memoryIndex == srcIndex) {
            memory.resize(srcIndex);
            return;
        }

        memcpy(destComponent, srcComponent, typeSize);

        // Update component pointer from srcComponent entity
        Array<std::pair<uint, uint>>& srcComponents = handleToEntityComponents(srcComponent->entity);
        for (uint i = 0; i < srcComponents.size(); i++) {
            if (componentID == srcComponents[i].first && srcIndex == srcComponents[i].second) {
                srcComponents[i].second = memoryIndex;
                break;
            }
        }

        memory.resize(srcIndex);
    }

    void ECS::addComponentInternal(EntityHandle handle, uint componentID, BaseECSComponent* entityComponent)
    {
        Array<std::pair<uint, uint>>& entityComponents = handleToEntityComponents(handle);

        ECSComponentCreateFunction createFn = BaseECSComponent::getComponentCreateFunction(componentID);
        std::pair<uint, uint> newPair;
        newPair.first = componentID;
        newPair.second = createFn(components[componentID], handle, entityComponent);
        entityComponents.push_back(newPair);
    }

    bool ECS::removeComponentInternal(EntityHandle handle, uint componentID)
    {   
        Array<std::pair<uint, uint>>& entityComponents = handleToEntityComponents(handle);
        for (uint i = 0; i < entityComponents.size(); i++) {
            if (componentID == entityComponents[i].first) {
                // Free Component memory
                deleteComponent(entityComponents[i].first, entityComponents[i].second);
                
                // Remove component "pointer" from components list
                uint srcIndex = entityComponents.size() - 1;
                uint destIndex = i;
                entityComponents[destIndex] = entityComponents[srcIndex];
                entityComponents.pop_back();

                return true;
            }
        }
        return false;
    }

    BaseECSComponent* ECS::getComponentInternal(EntityHandle handle, Array<byte>& memory, uint componentID)
    {
        Array<std::pair<uint, uint>>& entityComponents = handleToEntityComponents(handle);

        for (uint i = 0; i < entityComponents.size(); i++) {
            if (componentID == entityComponents[i].first) {
                return (BaseECSComponent*)&memory[entityComponents[i].second];
            }
        }

        return nullptr;
    }

    void ECS::updateSystem(BaseECSSystem* system, float delta)
    {
        static Array<BaseECSComponent*> componentParams;
        static Array<Array<byte>*> componentMemories;
        componentParams.resize(0);

        const Array<uint>& componentTypes = system->getComponentTypes();

        system->preUpdate(delta);
        if (componentTypes.size() == 1) 
        {
            uint componentID = componentTypes[0];
            size_t typeSize = BaseECSComponent::getComponentSize(componentID);
            Array<byte>& memory = components[componentID];
            for (uint j = 0; j < memory.size(); j += typeSize) {
                BaseECSComponent* component = (BaseECSComponent*)&memory[j];
                system->updateComponents(delta, &component);
            }
        }
        else {
            updateSystemWithMultipleComponents(system, delta,
                componentTypes, componentParams, componentMemories);
        }
        system->postUpdate(delta);
    }

    void ECS::updateSystems(ECSSystemList& systems, float delta)
    {
        for (uint i = 0; i < systems.size(); i++) {
            updateSystem(systems[i], delta);
        }
    }

    void ECS::updateSystemWithMultipleComponents(BaseECSSystem* system, float delta,
        const Array<uint>& componentTypes, Array<BaseECSComponent*>& componentParams, Array<Array<byte>*>& componentMemories)
    {
        const Array<uint>& componentFlags = system->getComponentFlags();

        componentParams.resize(std::max(componentParams.size(), componentTypes.size()));
        componentMemories.resize(std::max(componentParams.size(), componentTypes.size()));
        for (uint i = 0; i < componentTypes.size(); i++) {
            componentMemories[i] = &components[componentTypes[i]];
        }

        // Get Component Info
        uint minSizeIndex = findLeastCommonComponent(componentTypes, componentFlags);
        size_t typeSize = BaseECSComponent::getComponentSize(minSizeIndex);
        Array<byte>& memory = *(componentMemories[minSizeIndex]);

        for (uint i = 0; i < memory.size(); i += typeSize) {
            componentParams[minSizeIndex] = (BaseECSComponent*)&memory[i];
            EntityHandle handle = componentParams[minSizeIndex]->entity;

            bool isValid = true;
            for (uint j = 0; j < componentTypes.size(); j++) {
                if (j == minSizeIndex){
                    continue;
                }

                componentParams[j] = getComponentInternal(handle, *(componentMemories[j]), componentTypes[j]);
                if (componentParams[j] == nullptr && (componentFlags[j] & BaseECSSystem::FLAG_OPTIONAL) == 0) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                system->updateComponents(delta, &componentParams[0]);
            }
        }
    }

    uint ECS::findLeastCommonComponent(const Array<uint>& componentTypes, const Array<uint>& componentFlags)
    {
        uint minComponentNum = UINT_MAX;
        uint minIndex = 0;

        for (uint i = 0; i < componentTypes.size(); i++) {
            if ((componentFlags[i] & BaseECSSystem::FLAG_OPTIONAL) != 0) {
                continue;
            }

            size_t typeSize = BaseECSComponent::getComponentSize(componentTypes[i]);
            uint componentNum = components[componentTypes[i]].size() / typeSize;
            if (componentNum <= minComponentNum) {
                minComponentNum = componentNum;
                minIndex = i;
            }
        }

        return minIndex;
    }
}