#pragma once
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "stdafx.h"
#include <Windows.h>

#include <vector>
#include <string>
#include <algorithm>

#include "MessageLog.h"
#include "InventoryLog.h"
#include "TileLibrary.h"
#include "Cell.h"
#include "Point.h"
#include "ActorDef.h"
#include "Actor.h"
#include "PickupDef.h"
#include "Pickup.h"
#include "Dice.h"
#include "Hero.h"

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
	void doBattle(Actor* atkr, Actor* atkd); //Returns 0 if nobody died, 1 if atkr died, 2 if atkd died

	bool moveableCell(Point p);
	void onPlayerTurn(bool b, Point p);
	bool moveAI(Actor* monster);
	Point pickAIPoint(Point dir, bool random);

	void killMonster(Point loc);
	void killHero();
	void addPickup(Point loc);

	string registerInventoryClick();

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
	vector<PickupDef> pickupdefs;
	vector<Pickup*> pickups;
	Point screenOrientation;
	Point startPoint;
	Cell mainChar;
	TileLibrary lib;
	MessageLog log;
	InventoryLog invLog;
	Hero* hero;
	bool deadHero = false;
};

#endif