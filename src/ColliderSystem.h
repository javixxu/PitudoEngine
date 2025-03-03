#pragma once
#include <ecs/System.h>

class ColliderSystem :public System
{
public:
	ColliderSystem();
	~ColliderSystem();

	void Update(float deltaTime) override;
};

