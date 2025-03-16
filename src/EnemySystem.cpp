#include "EnemySystem.h"
#include <ecs/ECSManager.h>

#include "Transform.h"
#include "Enemy.h"

using namespace PitudoEngine;

namespace SuperPangGame {
	EnemySystem::EnemySystem():
		currentTimeSpawn(0.0f){
	}

	EnemySystem::~EnemySystem(){
	}

	void EnemySystem::Update(float deltaTime) {
		currentTimeSpawn += deltaTime;
		if (currentTimeSpawn >= timeSpawn) {
			//TO DO:: CREATE ENEMY
		}

		for (auto& entity : mEntities) {
			auto& transform = m_ecsManager->GetComponent<Transform>(entity);
			auto& enemy = m_ecsManager->GetComponent<Enemy>(entity);

			if(enemy.m_movementBehavior != nullptr)
				enemy.m_movementBehavior->Move(transform, deltaTime);
		} 
	}
}