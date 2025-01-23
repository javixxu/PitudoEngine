#include <iostream>
#include <tigr.h>

#include "Engine.h"

int main()
{
	PitudoEngine::Engine engine;
	if (!engine.init()) {
		return -1;
	}

	//while (engine.running()) {

	//}
	Tigr* screen = tigrWindow(320, 240, "Hello", 0);
	while (!tigrClosed(screen))
	{
		tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
		tigrPrint(screen, tfont, 120, 110, tigrRGB(0xff, 0xff, 0xff), "Hello, world.");
		tigrUpdate(screen);
	}
	tigrFree(screen);
	return 0;
}