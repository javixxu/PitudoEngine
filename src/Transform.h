#pragma once

#include <ecs/ecsDefinitions.h>
#include <vector>

#include "Vec2.h"

namespace PitudoEngine {
    class Transform : public Component {
    public:

        Vec2 position{ 0, 0 };      // Posicion en el mundo
        Vec2 scale{ 1, 1 };         // Escala 
        float rotation{ 0.0f };     // Rotacion en grados o radianes

        Transform() = default;
        Transform(const Vec2& pos, const Vec2& sc, float rot);
        ~Transform() = default;

        void ReadData(const std::unordered_map<std::string, std::string>& values, Entity e) override;

        Transform(const Transform& other) = default;
        Transform(Transform&& other) = default;
        Transform& operator=(const Transform& other) = default;
        Transform& operator=(Transform&& other) = default;
    };
}
