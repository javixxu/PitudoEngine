#include "RenderSystem.h"
#include <tigr/tigr.h>
#include <ecs/ECSManager.h>

#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
#include "Engine.h"

namespace PitudoEngine {
	RenderSystem::RenderSystem() :
		m_Window(nullptr) {
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
			auto& sprite = m_ecsManager->GetComponent<Sprite>(entity);
			sprite.Draw(m_Window);
		}

	#ifndef _DEBUG
		//ACTUALIZAR BUFFER
		tigrUpdate(m_Window);
	#endif // DEBUG
	}
}