#include "Enemy.h"
namespace SuperPangGame {
	Enemy::Enemy():
		m_movementBehavior(nullptr),m_numCollisions(1){
	}

	Enemy::Enemy(int numCollisions, IMovementBehavior* movement):
		m_movementBehavior(movement),m_numCollisions(numCollisions) {
	}

	void Enemy::OnCollisionCallBack(const Entity& _Msprite, const Entity& _Osprite){

		if (m_movementBehavior != nullptr) //POSIBLE CAMBIO DE MOVEMENT EN CASO DE COLLISION
			m_movementBehavior->OnCollision();

		m_numCollisions--; //reducir tamaño
		if (m_numCollisions <= 0) {
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
	void OrthoMovement::OnCollision(){
		InvertVelocity();
	}
	void OrthoMovement::InvertVelocity(){
		m_velocity = Vec2() - m_velocity;
	}
	//enemigo movimiento ortogonal
}