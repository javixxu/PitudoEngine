#include "PlayerController.h"
#include <tigr/tigr.h>
#include <ecs/ECSManager.h>

namespace SuperPangGame {
	PlayerController::PlayerController() :m_keyMoveRight(TK_RIGHT), m_keyMoveLeft(TK_LEFT) {
	}

	PlayerController::PlayerController(float playerSpeed, int playerKeyRight, int playerKeyLeft) :
		m_speed(playerSpeed), m_keyMoveRight(playerKeyRight), m_keyMoveLeft(playerKeyLeft) {
	}

	PlayerController::~PlayerController() {
	}

	void PlayerController::ReadData(const std::unordered_map<std::string, std::string>& values, Entity e){
		
		m_speed = std::stof(values.at("speed"));
		m_keyMoveRight = std::stoi(values.at("key_right"));
		m_keyMoveLeft = std::stoi(values.at("key_left"));
		printf("PlayerController Read, %d\n", e);
	}

	float PlayerController::getSpeed() {
		return m_speed;
	}

	void PlayerController::OnCollisionCallBack(const Entity& _MPlayer, const Entity& _Osprite){
	}
}