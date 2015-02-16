#pragma once

#include "stdafx.h"
#include <Windows.h>

#include <vector>
#include <string>
#include <algorithm>

#include "TileLibrary.h"
#include "Cell.h"
#include "Point.h"
#include "ActorDef.h"
#include "Actor.h"
#include "Dice.h"

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

	bool moveableCell(Point p);

	template<typename Func>
	void loop_world(Point start, Point end, Func f) {
		for (int x = start.x(); x < end.x(); x++) {
			for (int y = start.y(); y < end.y(); y++) {
				f(Point(x, y));
			}
		}
	}
private:
	int xScreenRes;
	int yScreenRes;
	int xRes;
	int yRes;
	int worldSize;
	vector<vector<Cell>> map;
	vector<Point> playableMap;
	vector<Actor*> monsters;
	Point screenOrientation;
	Point startPoint;
	Cell mainChar;
	TileLibrary lib;
};

