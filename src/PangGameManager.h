#pragma once
#include "GameManagerSystem.h"

namespace SuperPangGame {
	class PangGameManager : public PitudoEngine::GameManagerSystem {
		float restartTime = 2.5f;
		float m_currentTimeSpawn;
	public:
		PangGameManager();
		~PangGameManager();

		void Init() override;
		void Update(float deltatime) override;
	};
}
