#pragma comment(lib, "tilelibd.lib")

#include "stdafx.h"
#include <Windows.h>

#include "Character.h"
#include "Tile.h"
#include "Point.h"
#include "GameEngine.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//Set debug flag for mem alloc logging
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameEngine engine("roguelike", 800, 608, "tiles", 32, 3, 64); //25 x 19 tiles

	while (!engine.quitGame()) {
		engine.run();
	}


}