#include "GameManagerSystem.h"
#include <ecs/ECSManager.h>
#include "Engine.h"
#include "RenderDebugSystem.h"

namespace PitudoEngine {

	GameManagerSystem::GameManagerSystem(){
		SetGameState(GameState::START);
	}

	GameManagerSystem::~GameManagerSystem(){
	}

	void GameManagerSystem::Init(){
			//DEBUG GAMESTATE    
	#ifdef _DEBUG
			auto* renderDebugSystem = &m_ecsManager->GetSystem<RenderDebugSystem>();

			renderDebugSystem->addTextCallback([this]() {
				return this->GetStringGameState(this->GetGameState());
				}, Engine::GetWidth() / 2.0f - 25, 30.0, tigrRGB(255, 128, 255));

	#endif //DEBUG GAMESTATE 
	}

	GameManagerSystem::GameState GameManagerSystem::GetGameState() const{
		return m_GameState;
	}
	const std::string GameManagerSystem::GetStringGameState(GameManagerSystem::GameState state){
		switch (state) {
			ENUM_TO_STRING_CASE(GameState::START);
			ENUM_TO_STRING_CASE(GameState::PLAYING);
			ENUM_TO_STRING_CASE(GameState::END);
		default: return "UNKNOWN";
		}
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