#include "InputSystem.h"
#include "Vec2.h"
#include <tigr/tigr.h>

void InputSystem::Update(float _deltaTime){

	tigrMouse(m_screen, &m_mouseX, &m_mouseY,nullptr);
}

InputSystem::InputSystem(Tigr* _screen):m_screen(_screen){
}

bool InputSystem::isKeyDown(int _key){
	return !tigrClosed(m_screen) && tigrKeyDown(m_screen, _key);
}

bool InputSystem::isKeyPressed(int _key){
	return !tigrClosed(m_screen) && tigrKeyHeld(m_screen, _key);
}

Vec2 InputSystem::mousePosition(){
	return {(float)m_mouseX,(float)m_mouseY};
}
