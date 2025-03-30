#pragma once
#include <ecs/System.h>

class SpawnSystem : public System{
public:
	SpawnSystem();
	~SpawnSystem();
	void Update(float deltaTime) override;

	Entity SpawnEnemy(const Entity Entity);
};

