#include "RenderDebugSystem.h"
#include "Engine.h"

#include <tigr/tigr.h>
#include <ecs/ECSManager.h>

#include "Transform.h"
#include "Collider.h"
namespace PitudoEngine {
	RenderDebugSystem::RenderDebugSystem():
		m_Window(nullptr) {
	}

	RenderDebugSystem::~RenderDebugSystem(){
	}

	void RenderDebugSystem::setContext(Tigr* screen) {
		m_Window = screen;
	}

	void RenderDebugSystem::Update(float deltaTime){
		for (auto& entity : mEntities) {

			auto& transform = m_ecsManager->GetComponent<Transform>(entity);
			auto& collider = m_ecsManager->GetComponent<Collider>(entity);

			if (collider.m_colliderShape == ColliderShape::RECT) {
				Vec2 collPos = transform.position - (collider.m_size * collider.m_pivot);
				tigrFillRect(m_Window, (int)collPos.x, (int)collPos.y, (int)collider.m_size.x, (int)collider.m_size.y, tigrRGBA(0xFF, 0x00, 0xFF, 0x90));
			}
			else {
				Vec2 collPos = transform.position;
				tigrFillCircle(m_Window, (int)collPos.x, (int)collPos.y, (int)collider.m_size.x, tigrRGBA(0xFF, 0x00, 0xFF, 0x90));
			}

		}
		//TO DO:: GENERA 2 MEMORY LEAKS POR LA PUTISIMA CARA
		RenderDebug(deltaTime);

		tigrUpdate(m_Window);
	}

	void RenderDebugSystem::RenderDebug(float deltaTime) {
		Engine::printText(m_Window, "DeltaTime: " + Engine::sstr(deltaTime), { 30,30 });
		Engine::printText(m_Window, "FPS: " + Engine::sstr(1.0 / deltaTime), { 30,45 });
	}
}