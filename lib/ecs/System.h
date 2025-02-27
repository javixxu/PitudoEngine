#pragma once
#include "ecsDefinitions.h"

#include <set>

class ECSManager;

class System{
protected:
	ECSManager* m_ecsManager;
public:
	std::set<Entity> mEntities;
	System();
    virtual void Update(float deltaTime){};
};