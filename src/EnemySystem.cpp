#include "EnemySystem.h"
#include <ecs/ECSManager.h>
#include "Engine.h"

#include <vector>
#include <regex>

#include "Transform.h"
#include "Enemy.h"
#include "Collider.h"
#include "Sprite.h"

using namespace PitudoEngine;

namespace SuperPangGame {
	EnemySystem::EnemySystem():
		m_currentTimeSpawn(0.0f){
	}

	EnemySystem::~EnemySystem(){
		m_prefabs.clear();
	}

	void EnemySystem::Update(float deltaTime) {
		m_currentTimeSpawn += deltaTime;
		if (m_currentTimeSpawn >= m_timeSpawn) {
			//TO DO:: CREATE ENEMY
			CreateNewEnemy();
			m_currentTimeSpawn = 0.0f;
		}

		for (auto& entity : mEntities) {
			auto& transform = m_ecsManager->GetComponent<Transform>(entity);
			auto& enemy = m_ecsManager->GetComponent<Enemy>(entity);

			if(enemy.m_movementBehavior != nullptr)
				enemy.m_movementBehavior->Move(transform, deltaTime);
		} 
	}

	void EnemySystem::CreateFromOther(Entity Entity)
	{
		auto oldEnemy = &m_ecsManager->GetComponent<Enemy>(Entity);
		auto& transform = m_ecsManager->GetComponent<Transform>(Entity);
		auto sprite = &m_ecsManager->GetComponent<PitudoEngine::Sprite>(Entity);

		// Reducir tamaño y cambiar la imagen por una más pequeña
		std::string newPath = std::regex_replace(sprite->getPath(), std::regex("_(\\d+)\\.png"),
			"_" + std::to_string(oldEnemy->m_lifes) + ".png");

		// Crear dos nuevas entidades -1 y 1
		for (int i = -1; i <= 1; i += 2) {
			auto newEnt = m_ecsManager->CreateEntity();
			m_ecsManager->AddComponent<Transform>(newEnt, transform);

			auto& newTransform = m_ecsManager->GetComponent<Transform>(newEnt);
			newTransform.position += Vec2(10.0f * i, 0.0f); // Separar los enemigos horizontalmente

			m_ecsManager->AddComponent<PitudoEngine::Sprite>(newEnt, &newTransform, newPath, Vec2(0.5f));
			m_ecsManager->AddComponent<Collider>(newEnt, &newTransform, ColliderShape::CIRCLE, Vec2(0.5f));

			auto& coll = m_ecsManager->GetComponent<Collider>(newEnt);
			auto& nsprite = m_ecsManager->GetComponent<PitudoEngine::Sprite>(newEnt);
			coll.m_collisionLayer = "enemy";
			coll.m_size = nsprite.getImageSize() / 2.0f;

			// Clonar el comportamiento de movimiento si existe
			auto movementBehavior = oldEnemy->m_movementBehavior ? oldEnemy->m_movementBehavior->Clone() : nullptr;
			m_ecsManager->AddComponent<Enemy>(newEnt, oldEnemy->m_lifes, movementBehavior);
			auto& enemy = m_ecsManager->GetComponent<Enemy>(newEnt);

			coll.SetOnCollisionCallback(&enemy.OnCollisionCallBack);

			// Establecer velocidad en direcciones opuestas
			if (movementBehavior && oldEnemy->m_movementBehavior)
			{
				movementBehavior->m_velocity.x = oldEnemy->m_movementBehavior->m_velocity.x * i; // Velocidad positiva o negativa
			}
		}
	}

	void EnemySystem::CreateNewEnemy(){
		//int randomIndex = std::rand() % m_prefabs.size();

		//auto newEnt = m_ecsManager->CreateEntity();

		//m_ecsManager->AddComponent<Transform>(newEnt, Vec2(std::rand() % Engine::getWidth() - 100,  std::rand() % Engine::getHeight() - 100), Vec2(1.0,1.0),0.0f);

		//auto& newTransform = m_ecsManager->GetComponent<Transform>(newEnt);


		//m_ecsManager->AddComponent<PitudoEngine::Sprite>(newEnt, &newTransform, "newPath", Vec2(0.5f));
		//m_ecsManager->AddComponent<Collider>(newEnt, &newTransform, ColliderShape::CIRCLE, Vec2(0.5f));

		//auto& coll = m_ecsManager->GetComponent<Collider>(newEnt);
		//auto& nsprite = m_ecsManager->GetComponent<PitudoEngine::Sprite>(newEnt);
		//coll.m_collisionLayer = "enemy";
		//coll.m_size = nsprite.getImageSize() / 2.0f;
		//
		//// Clonar el comportamiento de movimiento si existe
		//m_ecsManager->AddComponent<Enemy>(newEnt,m_prefabs[randomIndex]->m_lifes, m_prefabs[randomIndex]->m_movementBehavior->Clone());
		//auto& enemy = m_ecsManager->GetComponent<Enemy>(newEnt);
		//coll.SetOnCollisionCallback(&enemy.OnCollisionCallBack);
	}

	void EnemySystem::SetEnemyPrefabs(const std::vector<Entity>& enemyPrefabs){
		m_prefabs = enemyPrefabs;
	}

}