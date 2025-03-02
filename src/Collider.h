#pragma once
#include <ecs/ecsDefinitions.h>
#include "Vec2.h"
#include "Transform.h"

template <typename T>
T clamp(T value, T min, T max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

enum class ColliderShape {
    RECT = 0,
    CIRCLE = 1
};

enum class CollisionType {
    BLOCK = 0,
    OVERLAP = 1
};

class Collider : public Component{
protected:
    const Transform* m_transform;

    ColliderShape m_colliderShape;
    Vec2 m_pOffset; // Desplazamiento relativo respecto al Transform
    Vec2 m_Size; // Tamaño relativo al Transform

    static bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2);
    static bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize);
    static bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2);

public:
    Collider();
    Collider(const Transform* transform, ColliderShape colliderShape = ColliderShape::RECT, Vec2 positionOffset = {}, Vec2 size = {1,1});
	virtual ~Collider() = default;

	bool collides(const Collider& other) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const;

    const Vec2& getOffset() const;
    void SetOffset(Vec2& newOffset);
};