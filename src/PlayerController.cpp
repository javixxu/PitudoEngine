#include "PlayerController.h"

#include <ecs/ECSManager.h>
#include <tigr/tigr.h>

#include "PangGameManager.h"
#include "Collider.h"


namespace SuperPangGame {
	PlayerController::PlayerController() :m_keyMoveRight(TK_RIGHT), m_keyMoveLeft(TK_LEFT),m_keyStartGame(TK_SPACE) {
	}

	PlayerController::PlayerController(float playerSpeed, int playerKeyRight, int playerKeyLeft, int keyStartGame) :
		m_speed(playerSpeed), m_keyMoveRight(playerKeyRight), m_keyMoveLeft(playerKeyLeft),m_keyStartGame(keyStartGame) {
	}

	PlayerController::~PlayerController() {
	}

	void PlayerController::ReadData(const std::unordered_map<std::string, std::string>& values, Entity e){
		
		m_speed = std::stof(values.at("speed"));
		m_keyMoveRight = std::stoi(values.at("key_right"));
		m_keyMoveLeft = std::stoi(values.at("key_left"));
		m_keyStartGame = std::stoi(values.at("key_start"));

		//Set callBack
		auto* coll = &ECSManager::getInstance().GetComponent<Collider>(e);

		assert(coll && "Collider Not Found Reading Data.");

		coll->SetOnCollisionCallback(&this->OnCollisionCallBack);


		printf("PlayerController Read, %d\n", e);
	}

	float PlayerController::GetSpeed() {
		return m_speed;
	}

	int PlayerController::GetKeyRight()
	{
		return m_keyMoveRight;
	}

	int PlayerController::GetKeyLeft()
	{
		return m_keyMoveLeft;
	}

	int PlayerController::GetKeyStart()
	{
		return m_keyStartGame;
	}

	void PlayerController::OnCollisionCallBack(const Entity& _MPlayer, const Entity& _OEntity){

		auto& ecsManager = ECSManager::getInstance();

		Collider& mCollider = ecsManager.GetComponent<Collider>(_MPlayer);
		Collider& oCollider = ecsManager.GetComponent<Collider>(_OEntity);

		PlayerController& mController = ecsManager.GetComponent<PlayerController>(_MPlayer);

		//Player Lose
		if (oCollider.m_collisionLayer == "enemy") {
			printf("PLAYER DEAD \n");

			ecsManager.GetSystem<PangGameManager>().SetGameState(GameManagerSystem::GameState::END);
		}
	}
}