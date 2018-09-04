#pragma once

namespace upp
{
    // Datatypes
    // Integers
    typedef int32_t int32;
    typedef int64_t int64;
    typedef int16_t int16;
    typedef int8_t int8;

    typedef uint32_t uint32;
    typedef uint32 uint;
    typedef uint64_t uint64;
    typedef uint16_t uint16;
    typedef uint8_t uint8;
    typedef uint8 byte;

    // ECS Stuff
    // Forward Declaration for functionpointer
    struct BaseECSComponent;

    typedef void* EntityHandle;

    typedef uint(*ECSComponentCreateFunction)(Array<byte>& memory, EntityHandle handle, BaseECSComponent* comp);
    typedef void(*ECSComponentFreeFunction)(BaseECSComponent* comp);
}
