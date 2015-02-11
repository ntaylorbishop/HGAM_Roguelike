#include "GameEngine.h"

//Structors
GameEngine::GameEngine(char* title, int xScreenRes, int yScreenRes, char* tiles, int tileSize, int tileRes, int worldSize) {
	lib.init(title, xScreenRes, yScreenRes, tiles, tileSize, tileRes);
	this->worldSize = worldSize;

	screenOrientation.setx((lib.res().x() / 2));
	screenOrientation.sety((lib.res().y() / 2));
	startPoint = screenOrientation;

	//Set up Character point
	mainChar.setCoords(screenOrientation);
	mainChar.setTile(201);
	mainChar.setTileType(3);

	//Initialize the outer map vector
	for (int i = 0; i < worldSize; i++) {
		vector<Tile> v;
		map.push_back(v);
	}

	//Generate the map boundaries
	loop_world(worldSize, [this](Point p) {
		Tile c(p, 2, 0x103, 0);
		map[p.x()].push_back(c);

	});
	/*for (int x = 0; x < worldSize; x++) {
		for (int y = 0; y < worldSize; y++) {
			Point p(x, y);
			Tile c(p, 2, 0x103, 0);
			map.at(x).push_back(c);
		}
	}*/

	//Generate the random rooms
	for (int i = 0; i < rand() % 130 + 100; i++) {
		Point pStart((rand() % 55 + 1), (rand() % 55 + 1));
		Point pEnd(pStart.x() + (rand() % 6 + 3), pStart.y() + (rand() % 6 + 3));

		fillBox(pStart, pEnd);
	}

	//Flood fill to connect the world
	int currZone = 0;
	vector<int> zoneSize;
	for (int x = 0; x < worldSize; x++) {
		for (int y = 0; y < worldSize; y++) {
			if (map.at(x).at(y).getTileType() != 2 && map.at(x).at(y).getZone() == 0) {
				currZone++;
				int size = floodFill(map.at(x).at(y).getCoords(), currZone, 0);
				zoneSize.push_back(size);
			}
		}
	}

	//Get biggest zone in array
	int max = zoneSize[0];
	int largestZone = 0;

	for (int i = 1; i < zoneSize.size(); i++) {
		if (zoneSize[i] > max) {
			largestZone = i;
			max = zoneSize[i];
		}
	}
	largestZone++; //Offset for vector index

	//Get rid of everything but largest zone
	for (int x = 0; x < worldSize - 1; x++) {
		for (int y = 0; y < worldSize - 1; y++) {
			if (map[x][y].getZone() != largestZone) {
				map[x][y].setTile(0x103);
				map[x][y].setTileType(2);
			}
		}
	}

	//Set player starting position
	vector<Point> possibleStartPoints;
	for (int x = 0; x < worldSize - 1; x++) {
		for (int y = 0; y < worldSize - 1; y++) {
			if (map[x][y].getZone() != 0 && map[x][y].getTileType() != 2)
				possibleStartPoints.push_back(map[x][y].getCoords());
		}
	}
	
	int startPos = rand() % possibleStartPoints.size();
	screenOrientation = possibleStartPoints[startPos];
	startPoint = screenOrientation;
}
GameEngine::~GameEngine() {
}

//main
void GameEngine::run() {
	lib.framestart();

	//Move char left, right, up, and down
	if (!KEYBOARDLAYOUT) {
		//DVORAK configuration
		if (lib.keywentdown("left") || lib.keywentdown("a")) {
			Point p(screenOrientation.x() - 1, screenOrientation.y());
			if (map[p.x()][p.y()].getTileType() != 2) {
				screenOrientation.setx(screenOrientation.x() - 1);
			}
		}
		else if (lib.keywentdown("up") || lib.keywentdown(",")) {
			Point p(screenOrientation.x(), screenOrientation.y() - 1);
			if (map[p.x()][p.y()].getTileType() != 2) {
				screenOrientation.sety(screenOrientation.y() - 1);
			}
		}
		else if (lib.keywentdown("right") || lib.keywentdown("e")) {
			Point p(screenOrientation.x() + 1, screenOrientation.y());
			if (map[p.x()][p.y()].getTileType() != 2) {
				screenOrientation.setx(screenOrientation.x() + 1);
			}
		}
		else if (lib.keywentdown("down") || lib.keywentdown("o")) {
			Point p(screenOrientation.x(), screenOrientation.y() + 1);
			if (map[p.x()][p.y()].getTileType() != 2) {
				screenOrientation.sety(screenOrientation.y() + 1);
			}
		}
	}
	else {
		//QWERTY configuration
		if (lib.keywentdown("left") || lib.keywentdown("a")) {
			Point p(screenOrientation.x() - 1, screenOrientation.y());
			if (map[p.x()][p.y()].getTileType() != 2) {
				screenOrientation.setx(screenOrientation.x() - 1);
			}
		}
		else if (lib.keywentdown("up") || lib.keywentdown("w")) {
			Point p(screenOrientation.x(), screenOrientation.y() - 1);
			if (map[p.x()][p.y()].getTileType() != 2) {
				screenOrientation.sety(screenOrientation.y() - 1);
			}
		}
		else if (lib.keywentdown("right") || lib.keywentdown("d")) {
			Point p(screenOrientation.x() + 1, screenOrientation.y());
			if (map[p.x()][p.y()].getTileType() != 2) {
				screenOrientation.setx(screenOrientation.x() + 1);
			}
		}
		else if (lib.keywentdown("down") || lib.keywentdown("s")) {
			Point p(screenOrientation.x(), screenOrientation.y() + 1);
			if (map[p.x()][p.y()].getTileType() != 2) {
				screenOrientation.sety(screenOrientation.y() + 1);
			}
		}
	}

	drawMap();
}

bool GameEngine::quitGame() {
	return lib.keywentdown("escape");
}
void GameEngine::drawMap() {
	int xWorld = screenOrientation.x() - (lib.res().x() / 2);
	int yWorld = screenOrientation.y() - (lib.res().y() / 2);
	int yWorldOrig = yWorld;

	for (int xScreen = 0; xScreen < lib.res().x(); xScreen++) {
		yWorld = yWorldOrig;

		for (int yScreen = 0; yScreen < lib.res().y(); yScreen++) {
			Point p(xWorld, yWorld);
			Point d(xScreen, yScreen);

			if (xWorld < 0 || yWorld < 0 || xWorld > worldSize - 1 || yWorld > worldSize - 1) {
				Tile t(d, 0, 0x103, 0);
				lib.rendertile(t.getTile(), d);
			}
			else {
				Tile t = map[xWorld][yWorld];
				lib.rendertile(t.getTile(), d);
			}
			yWorld++;
		}
		xWorld++;
	}

	//Draw char
	lib.rendertile(mainChar.getTile(), mainChar.getCoords());
}

void GameEngine::fillBox(Point pStart, Point pEnd) {
	for (int i = pStart.x(); i < pEnd.x(); i++) {
		for (int j = pStart.y(); j < pEnd.y(); j++) {
			map[i][j].setTile(0x100);
			map[i][j].setTileType(1);
		}
	}
}

int GameEngine::floodFill(Point loc, int zone, int size) {
	if (!(loc.x() < 0 || loc.x() > 63 || loc.y() < 0 || loc.y() > 63)) {
		if (map[loc.x()][loc.y()].getZone() != 0 || map[loc.x()][loc.y()].getTileType() == 2)
			return 1;
		else if (map[loc.x()][loc.y()].getZone() == 0 && map[loc.x()][loc.y()].getTileType() != 2) {
			map[loc.x()][loc.y()].setZone(zone);
			Point up(loc.x(), loc.y() - 1);
			Point left(loc.x() - 1, loc.y());
			Point right(loc.x() + 1, loc.y());
			Point down(loc.x(), loc.y() + 1);
			return size + floodFill(up, zone, size) + floodFill(left, zone, size) + floodFill(right, zone, size) + floodFill(down, zone, size);
		}
	}
	else
		return size;
}