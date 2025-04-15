//Javier Comas De Frutos javier.comas@live.u-tad.com

#include <iostream>

#include "Engine.h"


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(){
	PitudoEngine::Engine engine;

	if (!engine.Init()) return -1;
	
	engine.Run();

	if (!engine.Quit()) return -1;

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}