#include "EnemySystem.h"
#include <ecs/ECSManager.h>

#include "ReadFilesSystem.h"
#include "Engine.h"

#include <vector>
#include <regex>

#include "Transform.h"
#include "Enemy.h"
#include "Collider.h"
#include "Sprite.h"
#include "PangGameManager.h"

using namespace PitudoEngine;

namespace SuperPangGame {
	EnemySystem::EnemySystem():
		m_currentTimeSpawn(0.0f){
	}

	EnemySystem::~EnemySystem(){
		for (auto* prefab : m_prefabs)delete prefab;
		m_prefabs.clear();
	}

	void EnemySystem::Update(float deltaTime) {

		m_currentTimeSpawn += deltaTime;
		if (m_currentTimeSpawn >= m_timeSpawn) {
			CreateNewEnemy(); //Create ENEMY
			m_currentTimeSpawn = 0.0f;
		}

		for (auto& entity : mEntities) {
			auto& transform = m_ecsManager->GetComponent<Transform>(entity);
			auto& enemy = m_ecsManager->GetComponent<Enemy>(entity);

			if(enemy.m_movementBehavior != nullptr)
				enemy.m_movementBehavior->Move(transform, deltaTime);
		} 
	}

	void EnemySystem::Reset(){
		m_currentTimeSpawn = 0.0f;

		for (auto& entity : mEntities) {
			m_ecsManager->GetSystem<PangGameManager>().AddEntitiesToDestroy(&entity);
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
		int randomIndex = std::rand() % m_prefabs.size();

		Entity newEnt = m_ecsManager->CreateEntity();

		// Ejecutar cada lambda almacenada para construir los componentes en la nueva entidad
		for (const auto& constructor : m_prefabs[randomIndex]->componentConstructors) {
			constructor(newEnt);
		}
		auto& newTransform = m_ecsManager->GetComponent<Transform>(newEnt);
		newTransform.position = Vec2(
			static_cast<float>(75 + std::rand() % (Engine::GetWidth() - 125 - 75)),
			static_cast<float>(75 + std::rand() % (Engine::GetHeight() - 125 - 75))
		);
	}

	void EnemySystem::SetEnemyPrefabs(std::vector<PitudoEngine::PrefabData*> enemyPrefabs){
		m_prefabs = enemyPrefabs;
	}

}