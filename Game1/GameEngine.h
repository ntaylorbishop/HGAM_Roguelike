#pragma once

#include "stdafx.h"
#include <Windows.h>

#include <vector>
#include <string>

#include "tilelib.h"
#include "Tile.h"
#include "Point.h"
#include "Character.h"

//I use DVORAK, change to false when turning in for QWERTY
#define KEYBOARDLAYOUT false

using namespace std;

class GameEngine {
public:
	//Structors
	GameEngine(char* title, int xScreenRes, int yScreenRes, char* tiles, int tileSize, int tileRes, int worldSize);
	~GameEngine();

	void run();
	bool quitGame();

	void drawMap();
	int getTileAtLoc(Point p);
	void fillBox(Point pStart, Point pEnd);
	void moveScreen();
private:
	int xScreenRes;
	int yScreenRes;
	int xRes;
	int yRes;
	int worldSize;
	vector<Tile> map;
	vector<Tile> screen;
	Point screenOrientation;
	Point startPoint;
	Tile mainChar;
};

