#pragma once

#include "stdafx.h"
#include <Windows.h>

#include <vector>
#include <string>

#include "TileLibrary.h"
#include "Tile.h"
#include "Point.h"
#include "Character.h"

//I use DVORAK, change to false when turning in for QWERTY
#define KEYBOARDLAYOUT true

using namespace std;

class GameEngine {
public:
	//Structors
	GameEngine(char* title, int xScreenRes, int yScreenRes, char* tiles, int tileSize, int tileRes, int worldSize);
	~GameEngine();

	void run();
	bool quitGame();

	void drawMap();
	void fillBox(Point pStart, Point pEnd);
	int floodFill(Point loc, int zone, int size);
private:
	int xScreenRes;
	int yScreenRes;
	int xRes;
	int yRes;
	int worldSize;
	vector<vector<Tile>> map;
	Point screenOrientation;
	Point startPoint;
	Tile mainChar;
	TileLibrary lib;
};

