#pragma once
#include "ecsDefinitions.h"
#include <set>

class System{
public:
	std::set<Entity> mEntities;
    virtual void Update(float deltaTime){};
};