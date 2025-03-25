#include "SpawnSystem.h"
#include "ecs/ECSManager.h"
SpawnSystem::SpawnSystem(){

}

SpawnSystem::~SpawnSystem(){

}

void SpawnSystem::Update(float deltaTime)
{
}

Entity SpawnSystem::SpawnEntity(const Entity Entity)
{
	auto ent = m_ecsManager->CreateEntity();
	//TO DO:: COPY COMPONENTS
	
	return ent;
}
