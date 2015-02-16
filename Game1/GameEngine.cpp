#include "GameEngine.h"

//Structors
GameEngine::GameEngine(char* title, int xScreenRes, int yScreenRes, char* tiles, int tileSize, int tileRes, int worldSize) {
	lib.init(title, xScreenRes, yScreenRes, tiles, tileSize, tileRes);
	this->worldSize = worldSize;

	screenOrientation = lib.res() / 2;
	startPoint = screenOrientation;

	//Set up Character point
	mainChar.setLoc(screenOrientation);
	mainChar.setTile(0x0AC);
	mainChar.setTileType(3);

	//Initialize the outer map vector
	for (int i = 0; i < worldSize; i++) {
		vector<Cell> v;
		map.push_back(v);
	}

	//Generate the map boundaries
	loop_world(Point(0, 0), Point(worldSize, worldSize), [this](Point p) {
		Cell c(p, 2, 0x103, 0);
		map[p.x()].push_back(c);

	});

	//Generate the random rooms
	for (int i = 0; i < rand() % 130 + 100; i++) {
		Point pStart((rand() % 55 + 1), (rand() % 55 + 1));
		Point pEnd(pStart.x() + (rand() % 6 + 3), pStart.y() + (rand() % 6 + 3));

		fillBox(pStart, pEnd);
	}

	//Flood fill to connect the world
	int currZone = 0;
	vector<int> zoneSize;
	loop_world(Point(0, 0), Point(worldSize, worldSize), [&](Point p) {
		if (map[p.x()][p.y()].getCellType() != 2 && map[p.x()][p.y()].getZone() == 0) {
			currZone++;
			int size = floodFill(map[p.x()][p.y()].getLoc(), currZone, 0);
			zoneSize.push_back(size);
		}
	});

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
	loop_world(Point(0, 0), Point(worldSize - 1, worldSize - 1), [&](Point p) {
		if (map[p.x()][p.y()].getZone() != largestZone) {
			map[p.x()][p.y()].setTile(0x103);
			map[p.x()][p.y()].setTileType(2);
		}
	});

	//Set player starting position
	loop_world(Point(0, 0), Point(worldSize - 1, worldSize - 1), [&](Point p) {
		if (map[p.x()][p.y()].getZone() != 0 && map[p.x()][p.y()].getCellType() != 2)
			playableMap.push_back(map[p.x()][p.y()].getLoc());
	});

	//Add foliage
	vector<int> foliage = { 0x104, 0x171, 0x172, 0x173, 0x174 };
	for (int i = 0; i < rand() % 20 + 10; i++) {
		int fType = rand() % foliage.size();
		int spotOnMap = rand() % playableMap.size();
		Point pos = playableMap[spotOnMap];
		map[pos.x()][pos.y()].setTile(foliage[fType]);
	}

	//Add monsters
	ActorDef rat(Dice(1, 2), 1, 10, 0x0D9, "A mutated rat");
	ActorDef spider(Dice(1, 2), 1, 10, 0x0DF, "A big spider");
	ActorDef ant(Dice(1, 2), 1, 10, 0x080, "An angry ant");
	ActorDef bee(Dice(1, 2), 1, 10, 0x081, "A giant bee");
	ActorDef beetle(Dice(1, 2), 1, 10, 0x084, "A dung beetle");
	ActorDef snake(Dice(1, 2), 1, 10, 0x086, "A rattlesnake");
	ActorDef dingo(Dice(1, 2), 1, 10, 0x08C, "A rabid dingo");
	ActorDef fox(Dice(1, 2), 1, 10, 0x08D, "A mama fox");
	ActorDef plant(Dice(1, 2), 1, 10, 0x09C, "A mutated plant");
	ActorDef puppy(Dice(1, 2), 1, 10, 0x0DF, "A cute furry puppy dog");
	vector<ActorDef> actordefs = { rat, spider, ant, bee, beetle, snake, dingo, fox, plant, puppy };

	for (int i = 0; i < playableMap.size(); i++) {
		int chance = rand() % 30;
		int whichActor = rand() % actordefs.size();
		if (chance == 15) {
			monsters.push_back(new Actor(actordefs[whichActor], playableMap[i]));
			map[playableMap[i].x()][playableMap[i].y()].setActor(monsters.back());
		}
	}

	//Set starting pos
	int startPos = rand() % playableMap.size();
	screenOrientation = playableMap[startPos];
	startPoint = screenOrientation;
}
GameEngine::~GameEngine() {
	for (int i = 0; i < monsters.size(); i++)
		delete monsters[i];
	lib.shutdown();
}

//main
void GameEngine::run() {
	lib.framestart();

	//Move char left, right, up, and down //CHECK CHECK CHECK
	if (lib.keywentdown("left") || lib.keywentdown("a")) {
		Point p = screenOrientation - Point(1, 0);
		if (moveableCell(p))
			screenOrientation = p;
	}
	else if (lib.keywentdown("up") || lib.keywentdown("w")) {
		Point p = screenOrientation - Point(0, 1);
		if (moveableCell(p))
			screenOrientation = p;
	}
	else if (lib.keywentdown("right") || lib.keywentdown("d")) {
		Point p = screenOrientation + Point(1, 0);
		if (moveableCell(p))
			screenOrientation = p;
	}
	else if (lib.keywentdown("down") || lib.keywentdown("s")) {
		Point p = (screenOrientation + Point(0, 1));
		if (moveableCell(p))
			screenOrientation = p;
	}
	drawMap();
}

bool GameEngine::quitGame() {
	return lib.keywentdown("escape");
}
void GameEngine::drawMap() {
	Point world = screenOrientation - (lib.res() / 2);
	int yWorldOrig = world.y();

	for (int xScreen = 0; xScreen < lib.res().x(); xScreen++) {
		world.sety(yWorldOrig);
		for (int yScreen = 0; yScreen < lib.res().y(); yScreen++) {
			Point d(xScreen, yScreen);

			if (world.x() < 0 || world.y() < 0 || world.x() > worldSize - 1 || world.y() > worldSize - 1) {
				Cell t(d, 0, 0x103, 0);
				lib.rendertile(t.getTile(), d);
			}
			else {
				Cell t = map[world.x()][world.y()];
				if (t.getTile() != 0x100)
					lib.rendertile(0x100, d);
				lib.rendertile(t.getTile(), d);
				if (t.getActor() != NULL)
					lib.rendertile(t.getActor()->getActorDef().getTile(), d);
			}
			world = world + Point(0, 1);
		}
		world = world + Point(1, 0);
	}

	//Draw char
	lib.rendertile(mainChar.getTile(), mainChar.getLoc());
}

void GameEngine::fillBox(Point pStart, Point pEnd) {
	loop_world(pStart, pEnd, [&](Point p) {
		map[p.x()][p.y()].setTile(0x100);
		map[p.x()][p.y()].setTileType(1);
	});
}

int GameEngine::floodFill(Point loc, int zone, int size) {

	if (!(loc.x() < 0 || loc.x() > 63 || loc.y() < 0 || loc.y() > 63)) {
		if (map[loc.x()][loc.y()].getZone() != 0 || map[loc.x()][loc.y()].getCellType() == 2)
			return 1;
		else {
			map[loc.x()][loc.y()].setZone(zone);
			return size + floodFill(loc - Point(0, 1), zone, size) + floodFill(loc - Point(1, 0), zone, size)
				        + floodFill(loc + Point(1, 0), zone, size) + floodFill(loc + Point(0, 1), zone, size);
		}
	}
	else
		return size;
}

bool GameEngine::moveableCell(Point p) {
	Cell c = map[p.x()][p.y()];
	if (c.getCellType() != 2 && c.getActor() == NULL)
		return true;
	else
		return false;
}