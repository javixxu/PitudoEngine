#include "PlayersSystem.h"
#include <ecs/ECSManager.h>

#include "InputSystem.h"
#include "Transform.h"
#include "PlayerController.h"


namespace SuperPangGame {
	PlayersSystem::PlayersSystem() {
		inputSystem = &m_ecsManager->GetSystem<InputSystem>();
		gameManager = &m_ecsManager->GetSystem<PangGameManager>();
	}

	PlayersSystem::~PlayersSystem() {
	}

	void PlayersSystem::Update(float deltaTime) {
		for (auto& entity : mEntities) {
			auto& transform = m_ecsManager->GetComponent<Transform>(entity);
			auto& playerController = m_ecsManager->GetComponent<PlayerController>(entity);

			if (gameManager->GetGameState() == GameManagerSystem::GameState::START) {
				if (inputSystem->isKeyPressed(playerController.GetKeyStart())) {
					gameManager->SetGameState(GameManagerSystem::GameState::PLAYING);
				}
			}
			else if (gameManager->GetGameState() == GameManagerSystem::GameState::PLAYING) {
				if (inputSystem->isKeyPressed(playerController.GetKeyRight())) {
					transform.position.x += playerController.GetSpeed() * deltaTime;
				}
				if (inputSystem->isKeyPressed(playerController.GetKeyLeft())) {
					transform.position.x -= playerController.GetSpeed() * deltaTime;
				}
			}
			
		}
	}
}