#pragma once

#include "stdafx.h"
#include <Windows.h>

#include "tilelib.h"

class GameEngine {
public:
	GameEngine(char* title, int xScreenRes, int yScreenRes, char* tiles, int tileSize, int tileRes);
	~GameEngine();

	void framestart(int i);
	void rendertile(int tileImgLoc, int x, int y);
private:
	int xScreenRes;
	int yScreenRes;
	int xRes;
	int yRes;
};

