#include <iostream>

#include "Engine.h"

int main()
{
	PitudoEngine::Engine engine;
	if (!engine.Init()) return -1;
	
	engine.Run();

	if (!engine.Quit()) return -1;

	return 0;
}