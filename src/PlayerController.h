#pragma once
#include <ecs/ecsDefinitions.h>
#include "InputSystem.h"
using namespace PitudoEngine;

namespace SuperPangGame {
	class PlayerController : public Component
	{
	public:
		float m_speed = 150.0f;
		int m_keyMoveRight;
		int m_keyMoveLeft;

		PlayerController();
		PlayerController(float playerSpeed, int playerKeyRight, int playerKeyLeft);
		~PlayerController();

		void ReadData(const std::unordered_map<std::string, std::string>& values, Entity e) override;

		float getSpeed();

		static void OnCollisionCallBack(const Entity& _MPlayer, const Entity& _Osprite);
	};
}
