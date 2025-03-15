#include "ColliderSystem.h"
#include <ecs/ECSManager.h>
#include "Transform.h"
#include "Collider.h"

namespace PitudoEngine {
	ColliderSystem::ColliderSystem() {
	}

	ColliderSystem::~ColliderSystem() {
	}

	void ColliderSystem::Update(float deltaTime) {

		for (auto& entity1 : mEntities) {
			for (auto& entity2 : mEntities) {
				if (entity1 != entity2) {
					auto& collider1 = m_ecsManager->GetComponent<Collider>(entity1);
					auto& collider2 = m_ecsManager->GetComponent<Collider>(entity2);

					if (collider1.collides(collider2)) {

						printf("COLLISION detected between Entity %d and Entity %d\n", entity1, entity2);

						//Send Collision Methods CallBacks
						if (collider1.getOnCollisionCallback()) collider1.getOnCollisionCallback()(entity1,entity2);
						if (collider2.getOnCollisionCallback()) collider2.getOnCollisionCallback()(entity2,entity1);

						//TO DO:: HANDLE COLLISION
						//if (collider1.m_collisionType == CollisionType::BLOCK && collider2.m_collisionType == CollisionType::BLOCK) {
							//Seprate Objects
						//}
					}
				}
			}
		}
	}
}