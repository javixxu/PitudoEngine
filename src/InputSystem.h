#pragma once
#include <ecs/System.h>

class Vec2;
struct Tigr;
namespace PitudoEngine {

	class InputSystem : public System {
		Tigr* m_screen;
		int m_mouseX = 0, m_mouseY = 0;   // Pos del mouse
		int m_buttons = -1; //botn del raton k se ha clickeado
	public:
		InputSystem();
		void setContext(Tigr* screen);
		void Update(float _deltaTime) override;

		bool isKeyDown(int _key);
		bool isKeyPressed(int _key);
		Vec2 mousePosition();
	};
}
