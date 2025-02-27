#include "RenderSystem.h"
#include <ecs/ECSManager.h>
#include "Transform.h"
#include "MSprite.h"

RenderSystem::RenderSystem():m_Window(nullptr){
	
}

RenderSystem::~RenderSystem(){

}

void RenderSystem::setContext(Tigr* screen){
	m_Window = screen;
}

void RenderSystem::Update(float deltaTime){
	for (auto& entity : mEntities) {
		auto& transform = m_ecsManager->GetComponent<Transform>(entity);
		auto& sprite = m_ecsManager->GetComponent<MSprite>(entity);

		sprite.Draw(m_Window,transform.position);
	}
}
