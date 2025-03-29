#pragma once
#include <ecs/System.h>
#include <vector>

namespace PitudoEngine {
	class GameManagerSystem :public System
	{
		std::vector<const Entity*> m_EntitiesToDestroy;
	public:
		enum class GameState {
			START,
			PLAYING,
			END
		};
	private:
		GameState m_GameState;
	public:

		GameManagerSystem();
		~GameManagerSystem();

		GameState GetGameState() const;

		void SetGameState(GameState gameState);

		void AddEntitiesToDestroy(const Entity* entity);
		void CleanEntities();
	};
}
