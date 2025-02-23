#pragma once
#include <ecs/ecs.h>
#include "Vec2.h"
struct Tigr;

class InputSystem{
	Tigr* m_screen;
	int mouseX = 0, mouseY = 0;   // Pos del mouse

public:
	InputSystem(Tigr* _screen);
	void Update(float _deltaTime);

	bool isKeyDown(int _key);
	bool isKeyPressed(int _key);
	Vec2 mousePosition();
};

