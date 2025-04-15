#pragma once
#include <ecs/System.h>
#include <vector>

#define ENUM_TO_STRING_CASE(e) case e: return #e

namespace PitudoEngine {
	class GameManagerSystem :public System
	{
	public:
		enum class GameState {
			START,
			PLAYING,
			END
		};
	private:
		std::vector<const Entity*> m_EntitiesToDestroy;

		GameState m_GameState;

	public:

		GameManagerSystem();
		~GameManagerSystem();

		virtual void Init();
		virtual void Update(float deltaTime) override{};

		void SetGameState(GameState gameState);
		GameState GetGameState() const;
		const std::string GetStringGameState(GameManagerSystem::GameState state);

		void AddEntitiesToDestroy(const Entity* entity);
		void CleanEntities();
	};
}
