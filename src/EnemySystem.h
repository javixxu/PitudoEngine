#pragma once
#include <ecs/System.h>
#include <vector>

namespace SuperPangGame {
	class Enemy;
	class EnemySystem : public System
	{
		float m_timeSpawn = 5.0f;
		float m_currentTimeSpawn;

		std::vector<Entity> m_prefabs;
	public:
		EnemySystem();
		~EnemySystem();
		void Update(float deltaTime) override;

		void CreateFromOther(Entity oldEnemy);
		void CreateNewEnemy();

		void SetEnemyPrefabs(const std::vector<Entity>& enemyPrefabs);
	};
}
