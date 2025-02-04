//Javier Comas De Frutos javier.comas@live.u-tad.com
//
//main-cpp_ Defines ...
#include <iostream>

#include "Engine.h"

#include <minilua/minilua.h>

int main(){
	PitudoEngine::Engine engine;

	//TEMPORAL SE QUITARA
	lua_State* L = luaL_newstate();
	if (L == NULL)
		return -1;
	luaL_openlibs(L);
	luaL_loadstring(L, "print 'Initializing Lua'");
	lua_call(L, 0, 0);
	lua_close(L);
	//TEMPORAL SE QUITARA

	if (!engine.Init()) return -1;
	
	engine.Run();

	if (!engine.Quit()) return -1;

	return 0;
}