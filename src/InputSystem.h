#pragma once
#include <ecs/System.h>
class Vec2;
struct Tigr;

class InputSystem: public System{
	Tigr* m_screen;
	int m_mouseX = 0, m_mouseY = 0;   // Pos del mouse

public:
	InputSystem(Tigr* _screen);
	void Update(float _deltaTime) override;

	bool isKeyDown(int _key);
	bool isKeyPressed(int _key);
	Vec2 mousePosition();
};

