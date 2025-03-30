#include "SpawnSystem.h"
#include "ecs/ECSManager.h"

#include "Enemy.h"
#include "Collider.h"
#include "Transform.h"
#include "Sprite.h"

using namespace PitudoEngine;

SpawnSystem::SpawnSystem(){

}

SpawnSystem::~SpawnSystem(){

}

void SpawnSystem::Update(float deltaTime)
{
}

Entity SpawnSystem::SpawnEnemy(const Entity Entity)
{
	Transform& mTransform = m_ecsManager->GetComponent<Transform>(Entity);
	Collider& mCollider = m_ecsManager->GetComponent<Collider>(Entity);

	auto ent = m_ecsManager->CreateEntity();

	/*

	auto newEnt = m_ecsManager->CreateEntity();
	m_ecsManager->AddComponent<Transform>(newEnt,mTransform);
	m_ecsManager->AddComponent<Sprite>(newEnt, &ecsManager.GetComponent<Transform>(newEnt), "../data/images/amarillo_s.png", Vec2(0.5f));
	m_ecsManager->AddComponent<Collider>(newEnt, &ecsManager.GetComponent<Transform>(newEnt), ColliderShape::CIRCLE, Vec2(0.5f));
	m_ecsManager->AddComponent<Enemy>(newEnt, enemy1.m_numCollisions, new OrthoMovement({ 90,90 }));
	Enemy* enemy = &ecsManager.GetComponent<Enemy>(newEnt);

	auto coll = &ecsManager.GetComponent<Collider>(newEnt);
	auto sprite = &ecsManager.GetComponent<PitudoEngine::Sprite>(newEnt);
	coll->m_collisionLayer = "enemy";
	coll->m_size = sprite->getImageSize()/ 2.0f;
	coll->SetOnCollisionCallback(&enemy->OnCollisionCallBack);*/
	
	return ent;
}
