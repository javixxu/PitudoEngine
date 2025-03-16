#include "ColliderSystem.h"
#include <ecs/ECSManager.h>
#include "Transform.h"
#include "Collider.h"

namespace PitudoEngine {
	ColliderSystem::ColliderSystem(){
		m_ignoreLayers = std::unordered_map<std::string, std::string>();
	}

	ColliderSystem::~ColliderSystem() {
	}

	void ColliderSystem::Update(float deltaTime) {

		for (auto& entity1 : mEntities) {
			for (auto& entity2 : mEntities) {
				if (entity1 != entity2) {
					auto& collider1 = m_ecsManager->GetComponent<Collider>(entity1);
					auto& collider2 = m_ecsManager->GetComponent<Collider>(entity2);

					// Verificar si la capa de collider1 debe ignorar a collider2
					bool ignoreCollision = (m_ignoreLayers.find(collider1.m_collisionLayer) != m_ignoreLayers.end() &&
						m_ignoreLayers[collider1.m_collisionLayer] == collider2.m_collisionLayer);

					if (collider1.collides(collider2) && !ignoreCollision) {

						printf("COLLISION detected between Entity %d and Entity %d\n", entity1, entity2);

						//Send Collision Methods CallBacks
						if (collider1.getOnCollisionCallback()) collider1.getOnCollisionCallback()(entity1,entity2);
						if (collider2.getOnCollisionCallback()) collider2.getOnCollisionCallback()(entity2,entity1);
					}
				}
			}
		}
	}
	void ColliderSystem::AddIgnoreLayers(std::string layer1, std::string layer2){
		m_ignoreLayers.insert({ layer1,layer2 });
		m_ignoreLayers.insert({ layer2,layer1 });
	}
}