#include "Enemy.h"
#include <ecs/ECSManager.h>
#include "GameManagerSystem.h"

#include "Vec2.h"
#include "Collider.h"
#include "Sprite.h"
#include "Engine.h"

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


	void Enemy::OnCollisionCallBack(const Entity& _MEntity, const Entity& _OEntity){
		auto& ecsManager = ECSManager::getInstance();
		SuperPangGame::Enemy& enemy1 = ecsManager.GetComponent<Enemy>(_MEntity);

		
		Transform& mTransform = ecsManager.GetComponent<Transform>(_MEntity);
		Transform& oTransform = ecsManager.GetComponent<Transform>(_OEntity);

		Collider& mCollider = ecsManager.GetComponent<Collider>(_MEntity);
		Collider& oCollider = ecsManager.GetComponent<Collider>(_OEntity);

		Vec2 boxPosition = oTransform.position;
		Vec2 circlePos = mTransform.position;
		Vec2 halfSize = oCollider.m_size / 2.0f;
		float radius = mCollider.m_size.x;

		Vec2 closestPoint = {
			std::max(boxPosition.x - halfSize.x, std::min(circlePos.x, boxPosition.x + halfSize.x)),
			std::max(boxPosition.y - halfSize.y, std::min(circlePos.y, boxPosition.y + halfSize.y))
		};

		Vec2 delta = circlePos - closestPoint;
		float dist = delta.Length();
		float overlap = radius - dist;

		if (overlap > 0) {
			// Normalizamos el vector delta para obtener la dirección
			Vec2 normal = delta.Normalize();

			// Movemos `mTransform` fuera de la colisión
			mTransform.position += normal * overlap;
		}

		if (enemy1.m_movementBehavior != nullptr) {//POSIBLE CAMBIO DE MOVEMENT EN CASO DE COLLISION
			enemy1.m_movementBehavior->OnCollision(mTransform);
		}
		enemy1.m_numCollisions--; //reducir tamaño

		//DELETE THIS AND INSTANCE OTHER
		ecsManager.GetSystem<GameManagerSystem>().AddEntitiesToDestroy(&_MEntity);
		if (enemy1.m_numCollisions > 0) {

			//REDUCIR TAMAÑO
			/*auto newEnt = ecsManager.CreateEntity();
			ecsManager.AddComponent<Transform>(newEnt,mTransform.position,mTransform.scale,mTransform.rotation);
			ecsManager.AddComponent<PitudoEngine::Sprite>(newEnt, &ecsManager.GetComponent<Transform>(newEnt), "../data/images/amarillo_s.png", Vec2(0.5f));
			ecsManager.AddComponent<Collider>(newEnt, &ecsManager.GetComponent<Transform>(newEnt), ColliderShape::CIRCLE, Vec2(0.5f));
			ecsManager.AddComponent<Enemy>(newEnt, enemy1.m_numCollisions, new OrthoMovement({ 90,90 }));
			Enemy* enemy = &ecsManager.GetComponent<Enemy>(newEnt);

			auto coll = &ecsManager.GetComponent<Collider>(newEnt);
			auto sprite = &ecsManager.GetComponent<PitudoEngine::Sprite>(newEnt);
			coll->m_collisionLayer = "enemy";
			coll->m_size = sprite->getImageSize()/ 2.0f;
			coll->SetOnCollisionCallback(&enemy->OnCollisionCallBack);*/
		}
	}

	Enemy::~Enemy() {
		delete m_movementBehavior;
		m_movementBehavior = nullptr;
	}


	//enemigo movimiento ortogonal
	OrthoMovement::OrthoMovement(Vec2 _velocity) {
		m_velocity = _velocity;
		m_change =  std::rand() % 2;
	}
	void OrthoMovement::Move(Transform& transform, float deltaTime){
		transform.position += m_velocity * deltaTime;
	}

	IMovementBehavior* OrthoMovement::Clone() const{
		return new OrthoMovement(*this);
	}

	void OrthoMovement::OnCollision(const Transform& transform){
		if (Engine::getWidth() - transform.scale.x * 2 <= transform.position.x || transform.scale.x * 2 >= transform.position.x)
			m_velocity.x = -m_velocity.x;
		else m_velocity.y = -m_velocity.y;
	}
	//enemigo movimiento ortogonal

	//enemigo burbuja
	WaveMovement::WaveMovement(Vec2 _velocity, float gravity, float damping) : 
		m_gravity(gravity), m_damping(damping) {
		m_velocity = _velocity;
	}

	void WaveMovement::Move(Transform& transform, float deltaTime){
		m_velocity.y += m_gravity * deltaTime;

		transform.position += m_velocity * deltaTime;
	}

	IMovementBehavior* WaveMovement::Clone() const
	{
		return new WaveMovement(*this);
	}

	void WaveMovement::OnCollision(const Transform& transform){
		if(Engine::getWidth() - transform.scale.x * 2 <= transform.position.x || transform.scale.x * 2 >= transform.position.x)
			m_velocity.x = -m_velocity.x;
		else
			m_velocity.y = m_damping;
		//m_velocity = Vec2();
	}
	//enemigo burbuja
}