#include "GameEngine.h"

//Structors
GameEngine::GameEngine(char* title, int xScreenRes, int yScreenRes, char* tiles, int tileSize, int tileRes, int worldSize) {
	tl_init(title, xScreenRes, yScreenRes, tiles, tileSize, tileRes);
	this->worldSize = worldSize;
	//Set center point
	screenOrientation.setx((tl_xres() / 2));
	screenOrientation.sety((tl_yres() / 2));
	startPoint = screenOrientation;

	//Set up Character point
	mainChar.setCoords(screenOrientation);
	mainChar.setTile(201);
	mainChar.setTileType(3);

	//Generate the map boundaries
	for (int x = 0; x < worldSize; x++) {
		for (int y = 0; y < worldSize; y++) {
			Point p(x, y);
			Tile c(p, 0, 0x100);
			if (x == 0 || x == worldSize - 1 || y == 0 || y == worldSize - 1)
				c.setTile(0x127);
			else if ((x + y) % 2 == 0) {
				c.setTile(0x100);
			}
			else if ((x + y) % 2 != 0) {
				c.setTile(0x101);
			}
			map.push_back(c);
		}
	}

	/*Generate what will be shown on screen initially  DEPRECATED ATM
	for (int x = 0; x < tl_xres(); x++) {
		for (int y = 0; y < tl_yres(); y++) {
			Point p(x, y);
			screen.push_back(map.at(getTileAtLoc(p)));
		}
	}*/

	//Generate the random rooms
	for (int i = 0; i < rand() % 20 + 10; i++) {
		Point pStart((rand() % 58), (rand() % 58));
		Point pEnd(pStart.x() + (rand() % 6 + 3), pStart.y() + (rand() % 6 + 3));

		fillBox(pStart, pEnd);
	}
}
GameEngine::~GameEngine() {
}

//main
void GameEngine::run() {
	tl_framestart(0);

	//Move char left, right, up, and down
	if (!KEYBOARDLAYOUT) {
		//DVORAK configuration
		if (tl_keywentdown("left") || tl_keywentdown("a")) {
			screenOrientation.setx(screenOrientation.x() - 1);
		}
		else if (tl_keywentdown("up") || tl_keywentdown(",")) {
			screenOrientation.sety(screenOrientation.y() - 1);
		}
		else if (tl_keywentdown("right") || tl_keywentdown("e")) {
			screenOrientation.setx(screenOrientation.x() + 1);
		}
		else if (tl_keywentdown("down") || tl_keywentdown("o")) {
			screenOrientation.sety(screenOrientation.y() + 1);
		}
	}
	else {
		//QWERTY configuration
		if (tl_keywentdown("left") || tl_keywentdown("a")) {
			screenOrientation.setx(screenOrientation.x() - 1);
			
		}
		else if (tl_keywentdown("up") || tl_keywentdown("w")) {
			screenOrientation.sety(screenOrientation.y() - 1);
			
		}
		else if (tl_keywentdown("right") || tl_keywentdown("d")) {
			screenOrientation.setx(screenOrientation.x() + 1);
			
		}
		else if (tl_keywentdown("down") || tl_keywentdown("s")) {
			screenOrientation.sety(screenOrientation.y() + 1);
			
		}
	}

	drawMap();
}

bool GameEngine::quitGame() {
	return tl_keywentdown("escape");
}
void GameEngine::drawMap() {
	int xWorld = screenOrientation.x() - (tl_xres() / 2);
	int yWorld = screenOrientation.y() - (tl_yres() / 2);
	int yWorldOrig = yWorld;

	for (int xScreen = 0; xScreen < tl_xres(); xScreen++) {
		yWorld = yWorldOrig;
		for (int yScreen = 0; yScreen < tl_yres(); yScreen++) {
			Point p(xWorld, yWorld);
			if (xWorld < 0 || yWorld < 0 || xWorld > worldSize || yWorld > worldSize) {
				Point d(xScreen, yScreen);
				Tile t(d, 0, 0);
				tl_rendertile(t.getTile(), xScreen, yScreen);
			}
			else {
				Tile t = map.at(getTileAtLoc(p));
				tl_rendertile(t.getTile(), xScreen, yScreen);
			}
			yWorld++;
		}

		xWorld++;
	}

	//Draw char
	tl_rendertile(mainChar.getTile(), mainChar.getCoords().x(), mainChar.getCoords().y());
}
int GameEngine::getTileAtLoc(Point p) { //THIS MIGHT CAUSE ISSUES LATER
	int idx = 0;
	for (int i = 0; i < map.size(); i++) {
		if (map.at(i).getCoords().x() == p.x() && map.at(i).getCoords().y() == p.y()) {
			idx = i;
		}
	}
	return idx;
}

void GameEngine::fillBox(Point pStart, Point pEnd) {
	for (int i = pStart.x(); i < pEnd.x(); i++) {
		for (int j = pStart.y(); j < pEnd.y(); j++) {
			Point p(i, j);
			int idx = getTileAtLoc(p);
			if (i == pStart.x() || i == pEnd.x() || j == pStart.y() - 1 || j == pEnd.y() - 1)
				map.at(idx).setTile(0);
			else
				map.at(idx).setTile(0);
		}
	}
}
void GameEngine::moveScreen() {
	int xWorld = screenOrientation.x() - (tl_xres() / 2);
	int yWorld = screenOrientation.y() - (tl_yres() / 2);
	int yWorldOrig = yWorld;

	for (int xScreen = 0; xScreen < tl_xres(); xScreen++) {
		yWorld = yWorldOrig;
		for (int yScreen = 0; yScreen < tl_yres(); yScreen++) {
			Point p(xWorld, yWorld);
			if (xWorld < 0 || yWorld < 0 || xWorld > worldSize || yWorld > worldSize) {
				Point d(xScreen, yScreen);
				Tile t(d, 0, 0);
				tl_rendertile(t.getTile(), xScreen, yScreen);
			}
			else {
				Tile t = map.at(getTileAtLoc(p));
				tl_rendertile(t.getTile(), xScreen, yScreen);
			}
			yWorld++;
		}

		xWorld++;
	}
}