#pragma once
#include <ecs/ecsDefinitions.h>
#include "Vec2.h"
#include "Transform.h"
using namespace PitudoEngine;
class PitudoEngine::Transform;
namespace SuperPangGame {

    struct IMovementBehavior{
        Vec2 m_velocity; // Velocidad en cada eje

        virtual ~IMovementBehavior() {}
        virtual void Move(Transform& transform, float deltaTime) = 0;
        
        virtual IMovementBehavior* Clone() const = 0;
        virtual void OnCollision(const Transform& transform) {};
    };

    struct OrthoMovement : public IMovementBehavior{
        bool m_change;

        OrthoMovement(Vec2 _velocity);
        void Move(Transform& transform, float deltaTime) override;
        IMovementBehavior* Clone() const override;

        void OnCollision(const Transform& transform) override;
    };

    struct WaveMovement: public IMovementBehavior{
        float m_gravity; 
        float m_damping;  // Reduccion de la velocidad en cada rebote

        WaveMovement(Vec2 _velocity, float gravity, float damping);
        void Move(Transform& transform, float deltaTime) override;
        IMovementBehavior* Clone() const override;

        void OnCollision(const Transform& transform) override;
    };

    class Enemy :public Component {
        int m_numCollisions; 
    public:
        int m_lifes;
        IMovementBehavior* m_movementBehavior; // Comportamiento de movimiento
        Enemy();
        Enemy(int lifes,IMovementBehavior* movement);

        void ReadData(const std::unordered_map<std::string, std::string>& values, Entity e) override;

        Enemy(const Enemy& other) noexcept;
        Enemy(Enemy&& other) noexcept;
        Enemy& operator=(const Enemy& other) noexcept;
        Enemy& operator=(Enemy&& other) noexcept;


        static void OnCollisionCallBack(const Entity& _Msprite, const Entity& _Osprite);
        virtual ~Enemy();
    };

}