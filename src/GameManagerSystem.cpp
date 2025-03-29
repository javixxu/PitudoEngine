#include "GameManagerSystem.h"
#include <ecs/ECSManager.h>

namespace PitudoEngine {

	GameManagerSystem::GameManagerSystem(){
		SetGameState(GameState::START);
	}

	GameManagerSystem::~GameManagerSystem(){
	}

	GameManagerSystem::GameState GameManagerSystem::GetGameState() const{
		return m_GameState;
	}
	void GameManagerSystem::SetGameState(GameState gameState){
		m_GameState = gameState;
	}

	void GameManagerSystem::AddEntitiesToDestroy(const Entity* entity){
		m_EntitiesToDestroy.push_back(entity);
		//TO DO:: UNABLE DE ENTITY FOR DO NOTHING
	}
	void GameManagerSystem::CleanEntities(){
		for (auto* ent : m_EntitiesToDestroy) {
			m_ecsManager->DestroyEntity(*ent);
		}
		m_EntitiesToDestroy.clear();
	}
}