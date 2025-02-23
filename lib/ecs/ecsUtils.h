#pragma once

#include <cstdint>  // Para uint8_t

enum class ComponentType : uint8_t
{
    cType_Transform = 1,
    cType_Sprite = 2,
    cType_Collider = 3,
    cType_Input = 4
};