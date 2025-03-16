#pragma once
#include <ecs/ecsDefinitions.h>
#include "Vec2.h"
#include "Transform.h"
using namespace PitudoEngine;
namespace SuperPangGame {
    struct IMovementBehavior
    {
        virtual ~IMovementBehavior() {}
        virtual void Move(Transform& transform, float deltaTime) = 0;
        
        virtual IMovementBehavior* Clone() const = 0;
        virtual void OnCollision() {};

    };

    struct OrthoMovement : public IMovementBehavior
    {
        Vec2 m_velocity; // Velocidad en cada eje

        OrthoMovement(Vec2 _velocity);
        void Move(Transform& transform, float deltaTime) override;
        IMovementBehavior* Clone() const override;

        void OnCollision() override;
        void InvertVelocity();
    };

    class Enemy :public Component {
    public:
        int m_numCollisions; 
        IMovementBehavior* m_movementBehavior; // Comportamiento de movimiento
        Enemy();
        Enemy(int numCollisions,IMovementBehavior* movement);

        Enemy(const Enemy& other) noexcept;
        Enemy(Enemy&& other) noexcept;
        Enemy& operator=(const Enemy& other) noexcept;
        Enemy& operator=(Enemy&& other) noexcept;


        static void OnCollisionCallBack(const Entity& _Msprite, const Entity& _Osprite);
        virtual ~Enemy();
    };

}