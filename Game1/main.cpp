#include "stdafx.h"
#include <Windows.h>

#include "tilelib.h"
#include "Character.h"

//I use DVORAK, change to false when turning in for QWERTY
#define KEYBOARDLAYOUT true


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//Set debug flag for mem alloc logging
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Character* mainChar = new Character(0, 0);
	bool quitGame = false;

	tl_init("roguelike", 800, 608, "tiles", 32, 3);

	while (!quitGame) {
		tl_framestart(0);
		tl_rendertile(201, mainChar->getX(), mainChar->getY());

		//End game when player hits esc btn
		if (tl_keywentdown("escape"))
			quitGame = true;

		//Move char left, right, up, and down
		if (!KEYBOARDLAYOUT) {
			//DVORAK configuration
			if (tl_keywentdown("left") || tl_keywentdown("a"))
				mainChar->moveChar(0);
			else if (tl_keywentdown("up") || tl_keywentdown(","))
				mainChar->moveChar(1);
			else if (tl_keywentdown("right") || tl_keywentdown("e"))
				mainChar->moveChar(2);
			else if (tl_keywentdown("down") || tl_keywentdown("o"))
				mainChar->moveChar(3);
		}
		else {
			//QWERTY configuration
			if (tl_keywentdown("left") || tl_keywentdown("a"))
				mainChar->moveChar(0);
			else if (tl_keywentdown("up") || tl_keywentdown("w"))
				mainChar->moveChar(1);
			else if (tl_keywentdown("right") || tl_keywentdown("d"))
				mainChar->moveChar(2);
			else if (tl_keywentdown("down") || tl_keywentdown("s"))
				mainChar->moveChar(3);
		}
	}

}