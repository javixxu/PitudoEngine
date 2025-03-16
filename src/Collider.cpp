#include "Collider.h"
namespace PitudoEngine {
    bool Collider::checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2)
    {
        radius1 = std::abs(radius1);
        radius2 = std::abs(radius2);

        float deltaX = pos2.x - pos1.x;
        float deltaY = pos2.y - pos1.y;
        float distanceSquared = deltaX * deltaX + deltaY * deltaY;

        float radiusSum = radius1 + radius2;
        float radiusSumSquared = radiusSum * radiusSum;

        return distanceSquared <= radiusSumSquared;
    }

    bool Collider::checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize)
    {
        float xStart = rectSize.x >= 0 ? rectPos.x : rectPos.x + rectSize.x;
        float xEnd = rectSize.x >= 0 ? rectPos.x + rectSize.x : rectPos.x;

        float yStart = rectSize.y >= 0 ? rectPos.y : rectPos.y + rectSize.y;
        float yEnd = rectSize.y >= 0 ? rectPos.y + rectSize.y : rectPos.y;

        float closestX = clamp(circlePos.x, xStart, xEnd);
        float closestY = clamp(circlePos.y, yStart, yEnd);

        float deltaX = circlePos.x - closestX;
        float deltaY = circlePos.y - closestY;
        float distanceSquared = deltaX * deltaX + deltaY * deltaY;

        return distanceSquared <= (circleRadius * circleRadius);
    }

    bool Collider::checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2)
    {
        float x1Start = rectSize1.x >= 0 ? rectPos1.x : rectPos1.x + rectSize1.x;
        float x1End = rectSize1.x >= 0 ? rectPos1.x + rectSize1.x : rectPos1.x;

        float y1Start = rectSize1.y >= 0 ? rectPos1.y : rectPos1.y + rectSize1.y;
        float y1End = rectSize1.y >= 0 ? rectPos1.y + rectSize1.y : rectPos1.y;

        float x2Start = rectSize2.x >= 0 ? rectPos2.x : rectPos2.x + rectSize2.x;
        float x2End = rectSize2.x >= 0 ? rectPos2.x + rectSize2.x : rectPos2.x;

        float y2Start = rectSize2.y >= 0 ? rectPos2.y : rectPos2.y + rectSize2.y;
        float y2End = rectSize2.y >= 0 ? rectPos2.y + rectSize2.y : rectPos2.y;

        if (x1End <= x2Start || x2End <= x1Start) {
            return false;
        }

        if (y1End <= y2Start || y2End <= y1Start) {
            return false;
        }

        return true;
    }



    Collider::Collider() :m_transform(nullptr), m_colliderShape(ColliderShape::RECT), m_pivot(), m_Size(1) {
    }

    Collider::Collider(const Transform* transform, ColliderShape colliderShape, Vec2 pivot, Vec2 size,std::string collisionLayer) :
        m_transform(transform), m_colliderShape(colliderShape),
        m_pivot(pivot), m_Size(size),m_collisionLayer(collisionLayer) {
    }

    bool Collider::collides(const Collider& other) const {
        switch (m_colliderShape)
        {
        case ColliderShape::RECT:
            return other.collides(m_transform->position - (m_Size * m_pivot), m_Size);
            break;
        case ColliderShape::CIRCLE:
            return other.collides(m_transform->position, m_Size.x);
            break;
        }
        return false;
    }

    bool Collider::collides(const Vec2& circlePos, float circleRadius) const
    {
        switch (m_colliderShape)
        {
        case ColliderShape::RECT:
            return checkCircleRect(circlePos, circleRadius, m_transform->position - (m_Size * m_pivot), m_Size);
            break;
        case ColliderShape::CIRCLE:
            return checkCircleCircle(circlePos, circleRadius, m_transform->position, m_Size.x);
            break;
        }
        return false;
    }

    bool Collider::collides(const Vec2& rectPos, const Vec2& rectSize) const {
        switch (m_colliderShape)
        {
        case ColliderShape::RECT:
            return checkRectRect(rectPos, rectSize, m_transform->position - (m_Size * m_pivot), m_Size);
            break;
        case ColliderShape::CIRCLE:
            return checkCircleRect(m_transform->position, m_Size.x, rectPos, rectSize);
            break;
        }
        return false;
    }

    void Collider::SetOnCollisionCallback(CollisionCallbackFunc collisionCallback){
        m_OnCollisionCallBack = collisionCallback;
    }

    Collider::CollisionCallbackFunc Collider::getOnCollisionCallback() const{
        return m_OnCollisionCallBack;
    }
}