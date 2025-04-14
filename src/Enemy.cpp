#include "Enemy.h"
#include <ecs/ECSManager.h>
#include "GameManagerSystem.h"

#include "Vec2.h"
#include "Collider.h"
#include "Sprite.h"
#include "Engine.h"
#include "EnemySystem.h"

namespace SuperPangGame {
	Enemy::Enemy():
		m_movementBehavior(nullptr),m_lifes(1){
		m_numCollisions = m_lifes;
	}

	Enemy::Enemy(int lifes, IMovementBehavior* movement):
		m_movementBehavior(movement),m_lifes(lifes) {
		m_numCollisions = m_lifes;
	}

	void Enemy::ReadData(const std::unordered_map<std::string, std::string>& values, Entity e){

		auto itLifes = values.find("lifes");
		if (itLifes != values.end()) {
			m_lifes = std::stoi(itLifes->second);
		}
		else {
			m_lifes = 1; // valor por defecto
		}

		// Leer tipo de movimiento
		auto itMovement = values.find("movement");
		if (itMovement != values.end()) {
			const std::string movementType = itMovement->second;
			auto speed = Vec2(std::stof(values.at("velocity_x")), std::stof(values.at("velocity_y")));
			if (movementType == "ortho") {
				auto* move = new OrthoMovement(speed);
				m_movementBehavior = move;
			}
			else if (movementType == "wave") {
				auto* move = new WaveMovement(speed, std::stof(values.at("gravity")), std::stof(values.at("damping")));
				m_movementBehavior = move;
			}
			else {
				m_movementBehavior = nullptr;
			}
		}
		else {
			m_movementBehavior = nullptr;
		}

		m_numCollisions = 0;

		//Set callBack
		auto* coll = &ECSManager::getInstance().GetComponent<Collider>(e);

		assert(coll && "Collider Not Found Reading Data.");

		coll->SetOnCollisionCallback(&this->OnCollisionCallBack);
	}

	Enemy::Enemy(const Enemy& other) noexcept{
		*this = other;
	}

	Enemy::Enemy(Enemy&& other) noexcept{
		*this = std::move(other);
	}

	Enemy& Enemy::operator=(const Enemy& other) noexcept{
		this->m_numCollisions = other.m_numCollisions;
		this->m_lifes = other.m_lifes;
		this->m_movementBehavior = other.m_movementBehavior->Clone();
		return *this;
	}

	Enemy& Enemy::operator=(Enemy&& other) noexcept
	{
		this->m_numCollisions = other.m_numCollisions;
		this->m_lifes = other.m_lifes;
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

		enemy1.m_numCollisions--; //reducion rebotes

		if(enemy1.m_numCollisions <= 0 ){
		
			enemy1.m_numCollisions = enemy1.m_lifes;

			enemy1.m_lifes--;  //reducir tamaño

			//DELETE THIS AND INSTANCE OTHER
			ecsManager.GetSystem<GameManagerSystem>().AddEntitiesToDestroy(&_MEntity);

			if (enemy1.m_lifes > 0) {
				ecsManager.GetSystem<EnemySystem>().CreateFromOther(_MEntity);
			}
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