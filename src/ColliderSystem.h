#pragma once
#include <ecs/System.h>

class ColliderSystem :public System
{
	ColliderSystem();
	~ColliderSystem();

	void Update(float deltaTime) override;
};

