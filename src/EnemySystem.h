#pragma once
#include <ecs/System.h>



namespace SuperPangGame {
	class EnemySystem : public System
	{
		float timeSpawn = 5.0f;
		float currentTimeSpawn;
	public:
		EnemySystem();
		~EnemySystem();
		void Update(float deltaTime) override;
	};
}
