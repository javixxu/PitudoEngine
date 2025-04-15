#include "PangGameManager.h"

#include <ecs/ECSManager.h>
#include "Engine.h"
#include "RenderSystem.h"
#include "ScoreSystem.h"
#include "EnemySystem.h"

namespace SuperPangGame {
	PangGameManager::PangGameManager(): m_currentTimeSpawn(0.0f) {
	}

	PangGameManager::~PangGameManager() {
	}

	void PangGameManager::Init(){
		GameManagerSystem::Init();
		auto* renderSystem = &m_ecsManager->GetSystem<PitudoEngine::RenderSystem>();


		renderSystem->addTextCallback([this]() {
			switch (GetGameState()) {
			case GameState::START:
				return std::string("PRESS SPACE TO START");
			case GameState::END:
				return "Game Over\n  Your Score is " + std::to_string(m_ecsManager->GetSystem<ScoreSystem>().GetCurrentScore()) +
					"\n   Your Record is " + std::to_string(m_ecsManager->GetSystem<ScoreSystem>().GetRecordScore());
			default:
				return std::string(" "); // Si estoy jugando u otro estado, no mostrar nada
			}
		},
		PitudoEngine::Engine::GetWidth() / 2.0f - 75.0f, 60.0, tigrRGB(128, 128, 255));

	}

	void PangGameManager::Update(float deltatime){

		switch (GetGameState())	{
		case GameState::START:
			m_currentTimeSpawn = 0.0f;
			//SHOW TEXT PRESS SPACE TO START
			break;
		case GameState::PLAYING:
			break;
		case GameState::END:

			if (m_currentTimeSpawn == 0.0) { //ACTUALIZAR EL RECORD
				auto& scoreSys = m_ecsManager->GetSystem<ScoreSystem>();

				scoreSys.TrySetRecord();
				scoreSys.SaveBestRecord();

				//SCENE RESTART DESTROY::
				//  -- ENEMYS == DONE 
				//  -- RESET ENEMYS CONT == DONE
				//  -- RESET CURRESTSCORE

				m_ecsManager->GetSystem<EnemySystem>().Reset();
				scoreSys.Reset();
			}

			m_currentTimeSpawn += deltatime;
			printf("restart: %f \n", m_currentTimeSpawn);

			if (m_currentTimeSpawn >= 2.5f) {
				SetGameState(GameState::START);
			}
			break;
		}
	}
}