#pragma once

#include <ecs/ecsDefinitions.h>
#include <vector>

#include "Vec2.h"

namespace PitudoEngine {
    class Transform : public Component {
    public:

        //Transform* parent = nullptr;   // Transformacion padre
        //std::vector<Transform*> children; // Hijos

        Vec2 position{ 0, 0 };      // Posicion en el mundo
        Vec2 scale{ 1, 1 };         // Escala 
        float rotation{ 0.0f };     // Rotacion en grados o radianes

        Transform() = default;
        Transform(const Vec2& pos, const Vec2& sc, float rot);
        ~Transform() = default;

        Transform(const Transform& other) = default;
        Transform(Transform&& other) = default;
        Transform& operator=(const Transform& other) = default;
        Transform& operator=(Transform&& other) = default;

        //void SetParent(Transform* newParent);
        //void RemoveChild(Transform* child);  
    };
}
