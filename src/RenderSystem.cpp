#include "RenderSystem.h"
#include <tigr/tigr.h>
#include <ecs/ECSManager.h>

#include "Transform.h"
#include "MSprite.h"
#include "Engine.h"
namespace PitudoEngine {
	RenderSystem::RenderSystem() :m_Window(nullptr) {

	}

	RenderSystem::~RenderSystem() {

	}

	void RenderSystem::setContext(Tigr* screen) {
		m_Window = screen;
	}

	void RenderSystem::Update(float deltaTime) {
		tigrClear(m_Window, tigrRGB(0x80, 0x90, 0xa0));

		for (auto& entity : mEntities) {
			auto& transform = m_ecsManager->GetComponent<Transform>(entity);
			auto& sprite = m_ecsManager->GetComponent<MSprite>(entity);

			sprite.Draw(m_Window, transform.position);
		}

	#ifdef _DEBUG
		//RenderDebug(deltaTime);
	#endif // DEBUG

	//ACTUALIZAR BUFFER
		tigrUpdate(m_Window);
	}

	void RenderSystem::RenderDebug(float deltaTime) {
		Engine::printText(m_Window,"DeltaTime: " + Engine::sstr(deltaTime), { 30,30 });
		Engine::printText(m_Window,"FPS: " + Engine::sstr(1.0 / deltaTime), { 30,45 });
	}
}