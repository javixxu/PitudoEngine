#pragma once
#include <ecs/System.h>
#include "InputSystem.h"

namespace SuperPangGame {

	class PlayersSystem : public System {
		PitudoEngine::InputSystem* inputSystem = nullptr;
	public:
		PlayersSystem();
		~PlayersSystem();

		void Update(float deltaTime) override;
	};
}