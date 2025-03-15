#include "PlayersSystem.h"
#include <ecs/ECSManager.h>

#include "InputSystem.h"
#include "Transform.h"
#include "PlayerController.h"

namespace SuperPangGame {
	PlayersSystem::PlayersSystem() {
		inputSystem = &m_ecsManager->GetSystem<InputSystem>();
	}

	PlayersSystem::~PlayersSystem() {
	}

	void PlayersSystem::Update(float deltaTime) {
		for (auto& entity : mEntities) {
			auto& transform = m_ecsManager->GetComponent<Transform>(entity);
			auto& playerController = m_ecsManager->GetComponent<PlayerController>(entity);

			if (inputSystem->isKeyPressed(playerController.m_keyMoveRight)) {
				transform.position.x += playerController.m_speed * deltaTime;
			}
			if (inputSystem->isKeyPressed(playerController.m_keyMoveLeft)) {
				transform.position.x -= playerController.m_speed * deltaTime;
			}
		}
	}
}