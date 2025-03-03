#include "ColliderSystem.h"
#include <ecs/ECSManager.h>
#include "Transform.h"
#include "Collider.h"

ColliderSystem::ColliderSystem(){
}

ColliderSystem::~ColliderSystem(){
}

void ColliderSystem::Update(float deltaTime){

	for (auto& entity1: mEntities) {
		for (auto& entity2 : mEntities) {
			if (entity1 != entity2) {
				auto& collider1 = m_ecsManager->GetComponent<Collider>(entity1);
				auto& collider2 = m_ecsManager->GetComponent<Collider>(entity2);

				if (collider1.collides(collider2)) {
					//TO DO:: HANDLE COLLISION
					printf("COLLISION\n");
				}
			}
		}
	}
}
