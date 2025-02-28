#include "ECSManager.h"

void ECSManager::Init(){
    // Create pointers to each manager
    mComponentManager = std::make_unique<ComponentManager>();
    mEntityManager = std::make_unique<EntityManager>();
    mSystemManager = std::make_unique<SystemManager>();
}

void ECSManager::Close(){
    mComponentManager.reset();
    mEntityManager.reset();
    mSystemManager.reset();
}


// Entity methods
Entity ECSManager::CreateEntity(){
    return mEntityManager->CreateEntity();
}

void ECSManager::DestroyEntity(Entity entity){
    mEntityManager->DestroyEntity(entity);
    mComponentManager->EntityDestroyed(entity);
    mSystemManager->EntityDestroyed(entity);
}