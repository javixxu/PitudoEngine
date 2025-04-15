#pragma once
#include <ecs/System.h>
#include <vector>
#include <string>

namespace PitudoEngine {
	struct PrefabData;
}

namespace SuperPangGame {
	class Enemy;
	class EnemySystem : public System
	{
		float m_timeSpawn = 5.0f;
		float m_currentTimeSpawn;
		std::vector<PitudoEngine::PrefabData*> m_prefabs;
	public:
		EnemySystem();
		~EnemySystem();
		void Update(float deltaTime) override;
		void Reset() override;

		void CreateFromOther(Entity oldEnemy);
		void CreateNewEnemy();

		void SetEnemyPrefabs(std::vector<PitudoEngine::PrefabData*> enemyPrefabs);


	};
}
