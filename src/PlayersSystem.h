#pragma once
#include <ecs/System.h>
#include "InputSystem.h"
#include "PangGameManager.h"

namespace SuperPangGame {

	class PlayersSystem : public System {
		PitudoEngine::InputSystem* inputSystem = nullptr;
		PangGameManager* gameManager = nullptr;

	public:
		PlayersSystem();
		~PlayersSystem();

		void Update(float deltaTime) override;
	};
}