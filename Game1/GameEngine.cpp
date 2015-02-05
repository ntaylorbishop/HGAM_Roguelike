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

	//Initialize the outer map vector
	for (int i = 0; i < worldSize; i++) {
		vector<Tile> v;
		map.push_back(v);
	}

	//Generate the map boundaries
	for (int x = 0; x < worldSize; x++) {
		for (int y = 0; y < worldSize; y++) {
			Point p(x, y);
			Tile c(p, 2, 0x103, 0);
			map.at(x).push_back(c);
		}
	}

	//Generate the random rooms
	for (int i = 0; i < rand() % 130 + 100; i++) {
		Point pStart((rand() % 56 + 1), (rand() % 56 + 1));
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
	//string str = "\n\n" + to_string(largestZone) + "\n\n";
	//OutputDebugString(str.c_str());

	//Get rid of everything but largest zone
	for (int x = 0; x < worldSize - 1; x++) {
		for (int y = 0; y < worldSize - 1; y++) {
			if (map[x][y].getZone() != largestZone) {
				map[x][y].setTile(0x103);
				map[x][y].setTileType(2);
			}
		}
	}

	/*str = to_string(zoneSize.size());
	//OutputDebugString(to_string(currZone).c_str());
	for (int i = 0; i < zoneSize.size(); i++) {
		string str = to_string(i) + ":" + to_string(zoneSize.at(i)) + "|";
		OutputDebugString(str.c_str());
	}*/
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
			string str = to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getTileType()) + " " +
				to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getZone()) + "\n";
			OutputDebugString(str.c_str());
		}
		else if (tl_keywentdown("up") || tl_keywentdown(",")) {
			screenOrientation.sety(screenOrientation.y() - 1);
			string str = to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getTileType()) + " " +
				to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getZone()) + "\n";
			OutputDebugString(str.c_str());
		}
		else if (tl_keywentdown("right") || tl_keywentdown("e")) {
			screenOrientation.setx(screenOrientation.x() + 1);
			string str = to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getTileType()) + " " +
				to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getZone()) + "\n";
			OutputDebugString(str.c_str());
		}
		else if (tl_keywentdown("down") || tl_keywentdown("o")) {
			screenOrientation.sety(screenOrientation.y() + 1);
			string str = to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getTileType()) + " " +
				to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getZone()) + "\n";
			OutputDebugString(str.c_str());
		}
	}
	else {
		//QWERTY configuration
		if (tl_keywentdown("left") || tl_keywentdown("a")) {
			screenOrientation.setx(screenOrientation.x() - 1);
			string str = to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getTileType()) + " " +
				to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getZone()) + "\n";
			OutputDebugString(str.c_str());
		}
		else if (tl_keywentdown("up") || tl_keywentdown("w")) {
			screenOrientation.sety(screenOrientation.y() - 1);
			string str = to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getTileType()) + " " +
				to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getZone()) + "\n";
			OutputDebugString(str.c_str());
		}
		else if (tl_keywentdown("right") || tl_keywentdown("d")) {
			screenOrientation.setx(screenOrientation.x() + 1);
			string str = to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getTileType()) + " " +
				to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getZone()) + "\n";
			OutputDebugString(str.c_str());
		}
		else if (tl_keywentdown("down") || tl_keywentdown("s")) {
			screenOrientation.sety(screenOrientation.y() + 1);
			string str = to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getTileType()) + " " +
				to_string(map.at(screenOrientation.x()).at(screenOrientation.y()).getZone()) + "\n";
			OutputDebugString(str.c_str());
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

			if (xWorld < 0 || yWorld < 0 || xWorld > worldSize - 1 || yWorld > worldSize - 1) {
				Point d(xScreen, yScreen);
				Tile t(d, 0, 0, 0);
				tl_rendertile(t.getTile(), xScreen, yScreen);
			}
			else {
				Tile t = map.at(xWorld).at(yWorld);
				tl_rendertile(t.getTile(), xScreen, yScreen);
			}
			yWorld++;
		}
		xWorld++;
	}

	//Draw char
	tl_rendertile(mainChar.getTile(), mainChar.getCoords().x(), mainChar.getCoords().y());
}

void GameEngine::fillBox(Point pStart, Point pEnd) {
	for (int i = pStart.x(); i < pEnd.x(); i++) {
		for (int j = pStart.y(); j < pEnd.y(); j++) {
			Point p(i, j);
			map.at(i).at(j).setTile(0x100);
			map.at(i).at(j).setTileType(1);
		}
	}
}

int GameEngine::floodFill(Point loc, int zone, int size) {
	if (!(loc.x() < 0 || loc.x() > 63 || loc.y() < 0 || loc.y() > 63)) {
		//OutputDebugString("working");
		if (map.at(loc.x()).at(loc.y()).getZone() != 0 || map.at(loc.x()).at(loc.y()).getTileType() == 2)
			return 1;
		else if (map.at(loc.x()).at(loc.y()).getZone() == 0 && map.at(loc.x()).at(loc.y()).getTileType() != 2) {
			map.at(loc.x()).at(loc.y()).setZone(zone);
			//OutputDebugString(to_string(size).c_str());
			Point up(loc.x(), loc.y() - 1);
			Point left(loc.x() - 1, loc.y());
			Point right(loc.x() + 1, loc.y());
			Point down(loc.x(), loc.y() + 1);
			return size + floodFill(up, zone, size) + floodFill(left, zone, size) + floodFill(right, zone, size) + floodFill(down, zone, size);
		}
	}
	else {
		string str = "(" + to_string(loc.x()) + ", " + to_string(loc.y()) + ")";
		//OutputDebugString(str.c_str());
		return size;
	}
}