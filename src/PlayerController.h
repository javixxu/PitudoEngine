#pragma once
#include <ecs/ecsDefinitions.h>
#include "InputSystem.h"
using namespace PitudoEngine;

namespace SuperPangGame {
	class PlayerController : public Component{
	protected:
		float m_speed = 150.0f;
		int m_keyMoveRight;
		int m_keyMoveLeft;
		int m_keyStartGame;
	public:

		PlayerController();
		PlayerController(float playerSpeed, int playerKeyRight, int playerKeyLeft, int keyStartGame);
		~PlayerController();

		void ReadData(const std::unordered_map<std::string, std::string>& values, Entity e) override;

		float GetSpeed();
		int GetKeyRight();
		int GetKeyLeft();
		int GetKeyStart();

		static void OnCollisionCallBack(const Entity& _MPlayer, const Entity& _OEntity);
	};
}
