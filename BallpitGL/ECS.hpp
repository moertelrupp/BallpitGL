#pragma once

// Includes
#include "UppIncludes.hpp"
#include "BaseECSSystem.hpp"
#include "ECSSystemList.hpp"
#include "ECSComponent.hpp"

namespace upp
{
    // First uint is index in Array
    // Pair first uint is an entityID, second is the index in memory
    typedef std::pair<uint, Array<std::pair<uint, uint>>>* entityPtr;

    class ECS
    {
    public:
        ECS() {}
        ~ECS();

        // Entity methods
        EntityHandle makeEntity(BaseECSComponent** entityComponents, 
            const uint32* componentIDs, uint numComponents);
        void removeEntity(EntityHandle handle);

        template<class A>
        EntityHandle makeEntity(A& c1)
        {
            BaseECSComponent* components[] = { &c1 };
            uint32 componentIDs[] = { A::ID };
            return makeEntity(components, componentIDs, 1);
        }

        template<class A, class B>
        EntityHandle makeEntity(A& c1, B& c2)
        {
            BaseECSComponent* components[] = { &c1, &c2 };
            uint32 componentIDs[] = { A::ID, B::ID };
            return makeEntity(components, componentIDs, 2);
        }

        template<class A, class B, class C>
        EntityHandle makeEntity(A& c1, B& c2, C& c3)
        {
            BaseECSComponent* components[] = { &c1, &c2, &c3 };
            uint32 componentIDs[] = { A::ID, B::ID, C::ID };
            return makeEntity(components, componentIDs, 3);
        }

        template<class A, class B, class C, class D>
        EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4)
        {
            BaseECSComponent* components[] = { &c1, &c2, &c3, &c4 };
            uint32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID };
            return makeEntity(components, componentIDs, 4);
        }

        template<class A, class B, class C, class D, class E>
        EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5)
        {
            BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5 };
            uint32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID };
            return makeEntity(components, componentIDs, 5);
        }

        template<class A, class B, class C, class D, class E, class F>
        EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6)
        {
            BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6 };
            uint32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID };
            return makeEntity(components, componentIDs, 6);
        }

        template<class A, class B, class C, class D, class E, class F, class G>
        EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7)
        {
            BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7 };
            uint32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID };
            return makeEntity(components, componentIDs, 7);
        }

        template<class A, class B, class C, class D, class E, class F, class G, class H>
        EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8)
        {
            BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8 };
            uint32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID };
            return makeEntity(components, componentIDs, 8);
        }

        template<class A, class B, class C, class D, class E, class F, class G, class H, class I>
        EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8, I& c9)
        {
            BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9 };
            uint32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID, I::ID };
            return makeEntity(components, componentIDs, 9);
        }

        template<class A, class B, class C, class D, class E, class F, class G, class H, class I, class J>
        EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8, I& c9, J& c10)
        {
            BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10 };
            uint32 componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID, I::ID, J::ID };
            return makeEntity(components, componentIDs, 10);
        }



        // Component methods
        template<class Component>
        void addComponent(EntityHandle handle, Component* component);

        template<class Component>
        bool removeComponent(EntityHandle handle);

        template<class Component>
        Component* getComponent(EntityHandle handle);

        // System methods
        void updateSystem(BaseECSSystem* system, float delta);
        void updateSystems(ECSSystemList& systems, float delta);

    private:
        Map<uint, Array<byte>> components;
        Array<entityPtr> entities;

        // Entity Funcitons
        inline entityPtr handleToEntity(EntityHandle handle)
        {
            return (entityPtr)handle;
        }

        inline uint handleToEnityIndex(EntityHandle handle)
        {
            return handleToEntity(handle)->first;
        }

        inline Array<std::pair<uint, uint>>& handleToEntityComponents(EntityHandle handle)
        {
            return handleToEntity(handle)->second;
        }
        
        // Component Functions
        void deleteComponent(uint componentID, uint memoryIndex); // "Frees" the components memory
        void addComponentInternal(EntityHandle handle, uint componentID, BaseECSComponent* entityComponent);
        bool removeComponentInternal(EntityHandle handle, uint componentID);
        BaseECSComponent* getComponentInternal(EntityHandle handle, Array<byte>& memory, uint componentID);

        // System Functions
        void updateSystemWithMultipleComponents(BaseECSSystem* system, float delta,
            const Array<uint>& componentTypes, Array<BaseECSComponent*>& componentParams, Array<Array<byte>*>& componentMemories);

        uint findLeastCommonComponent(const Array<uint>& componentTypes, const Array<uint>& componentFlags);

        NULL_COPY_AND_ASSIGN(ECS);
    };

    // ----------------
    // |IMPLEMENTATION|
    // ----------------

    template<class Component>
    inline void ECS::addComponent(EntityHandle handle, Component* component)
    {
        addComponentInternal(handle, Component::ID, (BaseECSComponent*)component);
    }

    template<class Component>
    inline bool ECS::removeComponent(EntityHandle handle)
    {
        return removeComponentInternal(handle, Component::ID);
    }

    template<class Component>
    inline Component* ECS::getComponent(EntityHandle handle)
    {
        return (Component*)getComponentInternal(handle, components[Component::ID], Component::ID);
    }
}