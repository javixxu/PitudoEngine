#include "RenderSystem.h"
#include <tigr/tigr.h>
#include <ecs/ECSManager.h>

#include "Transform.h"
#include "Sprite.h"
#include "Collider.h"
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
			//auto& collider = m_ecsManager->GetComponent<Collider>(entity);
			auto& sprite = m_ecsManager->GetComponent<Sprite>(entity);
			sprite.Draw(m_Window);

	/*	#ifdef _DEBUG
			if (collider.m_colliderShape == ColliderShape::RECT) {
				Vec2 collPos = transform.position - (collider.m_Size * collider.m_pivot);
				tigrFillRect(m_Window, (int)collPos.x, (int)collPos.y, (int)collider.m_Size.x, (int)collider.m_Size.y, tigrRGBA(0x00, 0xFF, 0x00, 0x80));
			}
			else {
				Vec2 collPos = transform.position;
				tigrFillCircle(m_Window, (int)collPos.x, (int)collPos.y, (int)collider.m_Size.x, tigrRGBA(0x00, 0xFF, 0x00, 0x80));
			}
		#endif*/

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