#include "Enemy.h"
#include <ecs/ECSManager.h>

#include "Vec2.h"

using namespace PitudoEngine;

namespace SuperPangGame {
	Enemy::Enemy():
		m_movementBehavior(nullptr),m_numCollisions(1){
	}

	Enemy::Enemy(int numCollisions, IMovementBehavior* movement):
		m_movementBehavior(movement),m_numCollisions(numCollisions) {
	}

	Enemy::Enemy(const Enemy& other) noexcept{
		*this = other;
	}

	Enemy::Enemy(Enemy&& other) noexcept{
		*this = std::move(other);
	}

	Enemy& Enemy::operator=(const Enemy& other) noexcept{
		this->m_movementBehavior = other.m_movementBehavior->Clone();
		return *this;
	}

	Enemy& Enemy::operator=(Enemy&& other) noexcept
	{
		this->m_movementBehavior = other.m_movementBehavior;
		other.m_movementBehavior = nullptr;
		return *this;
	}


	void Enemy::OnCollisionCallBack(const Entity& _Msprite, const Entity& _Osprite){
		auto& ecsManager = ECSManager::getInstance();
		SuperPangGame::Enemy& enemy1 = ecsManager.GetComponent<Enemy>(_Msprite);

		if (enemy1.m_movementBehavior != nullptr) //POSIBLE CAMBIO DE MOVEMENT EN CASO DE COLLISION
			enemy1.m_movementBehavior->OnCollision();

		enemy1.m_numCollisions--; //reducir tamaño
		if (enemy1.m_numCollisions <= 0) {
			//TO DO:: ELIMINAR ENEMIGO
		}
		else{
			//REDUCIR TAMAÑO
		}
	}

	Enemy::~Enemy() {
		delete m_movementBehavior;
		m_movementBehavior = nullptr;
	}


	//enemigo movimiento ortogonal
	OrthoMovement::OrthoMovement(Vec2 _velocity)
		: m_velocity(_velocity) {
	}
	void OrthoMovement::Move(Transform& transform, float deltaTime){
		transform.position += m_velocity * deltaTime;
	}

	IMovementBehavior* OrthoMovement::Clone() const{
		return new OrthoMovement(*this);
	}

	void OrthoMovement::OnCollision(){
		InvertVelocity();
	}
	void OrthoMovement::InvertVelocity(){
		m_velocity = Vec2() - m_velocity;
	}
	//enemigo movimiento ortogonal
}