#include "GameEngine.h"

//Structors
GameEngine::GameEngine(char* title, int xScreenRes, int yScreenRes, char* tiles, int tileSize, int tileRes, int worldSize) {
	lib.init(title, xScreenRes, yScreenRes, tiles, tileSize, tileRes);
	this->worldSize = worldSize;

	screenOrientation = lib.res() / 2;
	startPoint = screenOrientation;

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
	int end = worldSize - 1;
	loop_world(Point(0, 0), Point(worldSize, worldSize), [&](Point p) {
		Cell& c = map[p.x()][p.y()];

		if (c.getZone() != largestZone ) {
			if ((p.x() + 1 < end && map[p.x() + 1][p.y()].getZone() == largestZone) || 
				(p.x() - 1 > 0   && map[p.x() - 1][p.y()].getZone() == largestZone) || 
				(p.y() + 1 < end && map[p.x()][p.y() + 1].getZone() == largestZone) || 
				(p.y() - 1 > 0   && map[p.x()][p.y() - 1].getZone() == largestZone) || 
				(p.x() - 1 > 0 && p.y() - 1 > 0     && map[p.x() - 1][p.y() - 1].getZone() == largestZone) ||
				(p.x() - 1 > 0 && p.y() + 1 < end   && map[p.x() - 1][p.y() + 1].getZone() == largestZone) || 
				(p.x() + 1 < end && p.y() - 1 > 0   && map[p.x() + 1][p.y() - 1].getZone() == largestZone) || 
				(p.x() + 1 < end && p.y() + 1 < end && map[p.x() + 1][p.y() + 1].getZone() == largestZone)) {
					c.setTile(0x103);
					c.setTileType(2);
			}
			else {
				c.setTile(0);
				c.setTileType(2);
			}
		}
		else if (c.getLoc().x() == end)
			c.setTile(0);
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
		map[pos.x()][pos.y()].setTileType(4);
	}

	//Add monsters
	ActorDef rat(Dice(2, 2), 0, 30, 0x0D9, "A mutated rat");
	ActorDef spider(Dice(2, 2), 0, 20, 0x0DF, "A big spider");
	ActorDef ant(Dice(2, 2), 0, 20, 0x080, "An angry ant");
	ActorDef bee(Dice(2, 2), 0, 20, 0x081, "A giant bee");
	ActorDef beetle(Dice(3, 1), 0, 20, 0x084, "A dung beetle");
	ActorDef snake(Dice(2, 2), 0, 30, 0x086, "A rattlesnake");
	ActorDef dingo(Dice(1, 1), 1, 30, 0x08C, "A rabid dingo");
	ActorDef fox(Dice(3, 2), 2, 30, 0x08D, "A mama fox");
	ActorDef plant(Dice(3, 2), 1, 30, 0x09C, "A mutated plant");
	ActorDef puppy(Dice(3, 2), 1, 20, 0x090, "A cute furry puppy dog");
	vector<ActorDef> actordefs = { rat, spider, ant, bee, beetle, snake, dingo, fox, plant, puppy };
	for (int i = 0; i < playableMap.size(); i++) {
		int chance = rand() % 30;
		int whichActor = rand() % actordefs.size();
		if (chance == 15) {
			monsters.push_back(new Actor(actordefs[whichActor], playableMap[i], false));
			map[playableMap[i].x()][playableMap[i].y()].setActor(monsters.back());
		}
	}

	//Add pickups
	pickupdefs = {
		PickupDef(0x230, "Health Potion", 0, [&]() { hero->setHP(hero->getHP() + 10); }),
		PickupDef(0x220, "Max Health Potion", 0, [&]() { hero->setMaxHP(hero->getActorDef().getMaxHP() + 5); }),
		PickupDef(0x2DC, "Crude Helmet", "Increases defense by 1", 1, [&]() {hero->setDEF(hero->getActorDef().getDEF() + 1); }, [&]() {hero->setDEF(hero->getActorDef().getDEF() - 1); }),
		PickupDef(0x337, "Worn Necklace", "Increases max health by 5", 2, [&]() { hero->setMaxHP(hero->getActorDef().getMaxHP() + 5); }, [&]() { hero->setMaxHP(hero->getActorDef().getMaxHP() - 5); }),
		PickupDef(0x2D0, "Tattered Shirt", "Increases max health by 5", 3, [&]() {hero->setMaxHP(hero->getActorDef().getMaxHP() + 5); }, [&]() { hero->setMaxHP(hero->getActorDef().getMaxHP() - 5); }),
		PickupDef(0x2E7, "Worn Leather Glove", "Increases defense by 1", 4, [&]() {hero->setDEF(hero->getActorDef().getDEF() + 1); }, [&]() {hero->setDEF(hero->getActorDef().getDEF() - 1); }),
		PickupDef(0x2E1, "Smelly Old Shoe", "Increases defense by 1", 5, [&]() {hero->setDEF(hero->getActorDef().getDEF() + 1); }, [&]() {hero->setDEF(hero->getActorDef().getDEF() - 1); }),
		PickupDef(0x3D1, "Standard Spell Journal", "Increases attack by 1", 6, [&]() {
			hero->setATK(Dice(hero->getActorDef().actorATK().getSides(), hero->getActorDef().actorATK().getRolls() + 1)); 
		}, [&]() {
			hero->setATK(Dice(hero->getActorDef().actorATK().getSides(), hero->getActorDef().actorATK().getRolls() - 1));
		}),
		PickupDef(0x260, "Crude Dagger", "Increases max attack by 2", 7, [&]() {
			hero->setATK(Dice(hero->getActorDef().actorATK().getSides() + 2, hero->getActorDef().actorATK().getRolls()));
		}, [&]() {
			hero->setATK(Dice(hero->getActorDef().actorATK().getSides() - 2, hero->getActorDef().actorATK().getRolls()));;
		}),
		PickupDef(0x2C0, "Broken Shield", "Increases defense by 2", 8, [&]() {hero->setDEF(hero->getActorDef().getDEF() + 1); }, [&]() {hero->setDEF(hero->getActorDef().getDEF() - 1); })
	};
	
	//Set starting pos
	int startPos = rand() % playableMap.size();
	screenOrientation = playableMap[startPos];
	startPoint = screenOrientation;
	ActorDef main(Dice(3, 4), 1, 100, 0x0AC, "The hero");
	hero = new Hero(main, screenOrientation, true);

	//Set up MessageLog / Inventory
	log.init(&lib);
	invLog.init(&lib, hero);
}
GameEngine::~GameEngine() {
	for (int i = 0; i < monsters.size(); i++)
		delete monsters[i];
	//delete hero;
	delete hero;
	for (int i = 0; i < pickups.size(); i++)
		delete pickups[i];
	lib.shutdown();
}

//main
void GameEngine::run() {
	lib.framestart();

	//Move the char left, right, up, and down
	if (!deadHero && !invLog.isGearOpen()) {
		onPlayerTurn((lib.keywentdown("left") || lib.keywentdown("a")), Point(-1, 0));
		onPlayerTurn((lib.keywentdown("up") || lib.keywentdown("w")), Point(0, -1));
		onPlayerTurn((lib.keywentdown("right") || lib.keywentdown("d")), Point(1, 0));
		onPlayerTurn((lib.keywentdown("down") || lib.keywentdown("s")), Point(0, 1));

		if (tl_buttonwentdown(1)) {
			string str = registerInventoryClick();
			if (!str.empty()) {
				string event = "Used a " + str + "!";
				log.registerEvent(event.c_str());
			}
		}
		if (tl_buttonwentdown(3)) {
			Pickup p;
			p = invLog.dropItem(lib.mouseLoc());
			OutputDebugString(p.getLoc().to_str().c_str());
			if (p.getLoc() != Point(-1, -1)) {
				string event = "Dropped the " + p.getPickupDef().getName() + "!";
				log.registerEvent(event.c_str());
			}
		}
	}
	else if (!deadHero && invLog.isGearOpen()) {
		if (tl_buttonwentdown(3)) {
			Pickup p = invLog.unequipGear(lib.mouseLoc());
			if (p.getLoc() != Point(-1, -1)) {
				string event = "Unequipped the " + p.getPickupDef().getName() + "!";
				log.registerEvent(event.c_str());
			}
		}
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
				Cell t(d, 0, 0, 0);
				lib.rendertile(t.getTile(), d);
			}
			else {
				Cell t = map[world.x()][world.y()];
				if (t.getTile() != 0x100 && t.getCellType() != 4)
					lib.rendertile(0, d);
				else if (t.getCellType() == 4)
					lib.rendertile(0x100, d);

				lib.rendertile(t.getTile(), d);

				if (t.getActor() != NULL)
					lib.rendertile(t.getActor()->getActorDef().getTile(), d);
				if (t.getPickup() != NULL)
					lib.rendertile(t.getPickup()->getPickupDef().getTile(), d);
			}
			world = world + Point(0, 1);
		}
		world = world + Point(1, 0);
	}

	//Draw char
	if (!deadHero)
		lib.rendertile(hero->getActorDef().getTile(), mainChar.getLoc());

	//Render MessageLog, InventoryLog
	log.renderMsgs();
	invLog.renderInventory();
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
void GameEngine::doBattle(Actor* atkr, Actor* atkd) {
	string heroHP = "HP: " + to_string(hero->getHP()) + "\n";
	OutputDebugString(heroHP.c_str());
	lib.play("OnHit");

	int atkrDMG = atkr->getATK() - atkd->getActorDef().getDEF();
	int atkdDMG = atkd->getATK() - atkr->getActorDef().getDEF();

	atkr->doDMG(atkdDMG);
	string atkrEvent;
	if(atkrDMG > 0)
		atkrEvent = atkr->getActorDef().getDESC() + " attacked " + atkd->getActorDef().getDESC() + " for " + to_string(atkrDMG) + "!";
	else
		atkrEvent = atkr->getActorDef().getDESC() + " missed!";
	log.registerEvent(atkrEvent);

	atkd->doDMG(atkrDMG);
	string atkdEvent;
	if (atkrDMG > 0)
		atkdEvent = atkd->getActorDef().getDESC() + " defended for " + to_string(atkdDMG) + "!";
	else
		atkdEvent = atkr->getActorDef().getDESC() + " missed!";
	log.registerEvent(atkdEvent);
	
	if (atkr->onDeath()) {
		log.registerEvent(atkr->getActorDef().getDESC() + " died!");
		if (atkr->isHero()) {
			lib.play("HeroOnDeath");
			killHero();
		}
		else
			killMonster(atkr->getLoc());
	}
	else if (atkd->onDeath()) {
		log.registerEvent(atkd->getActorDef().getDESC() + " died!");
		if (atkd->isHero()) {
			lib.play("HeroOnDeath");
			killHero();
		}
		else 
			killMonster(atkd->getLoc());
	}
}

bool GameEngine::moveableCell(Point p) {
	Cell c = map[p.x()][p.y()];
	if (c.getCellType() != 2 && c.getActor() == NULL)
		return true;
	else
		return false;
}
void GameEngine::onPlayerTurn(bool b, Point p) {
	if (b) {
		//Move Player
		Point d = p;
		p = p + screenOrientation;
		if (moveableCell(p)) {
			screenOrientation = p;
			hero->setLoc(hero->getLoc() + d);

			if (map[p.x()][p.y()].getPickup() != NULL)
				addPickup(p);
		}
		else if (map[p.x()][p.y()].getActor() != NULL)
			doBattle(hero, map[p.x()][p.y()].getActor());

		//Move AI
		for (int i = 0; i < monsters.size(); i++) {
			Point mLoc = monsters[i]->getLoc();
			Actor* m = map[mLoc.x()][mLoc.y()].getActor();
			if (moveAI(m))
				doBattle(m, hero);
		}
	}
}
bool GameEngine::moveAI(Actor* monster) {
	Point heroLoc = hero->getLoc();
	Point loc = monster->getLoc();
	int xDist = heroLoc.x() - loc.x();
	int yDist = heroLoc.y() - loc.y();
	int which = 0;

	Point dir(0, 0);

	if (xDist == 0 && yDist == 0)
		dir = Point(0, 0);
	else if (xDist == 0 && yDist != 0)
		dir = Point(0, yDist / abs(yDist));
	else if (xDist != 0 && yDist == 0)
		dir = Point(xDist / abs(xDist), 0);
	else if (xDist != 0 && yDist != 0)
		dir = Point(xDist / abs(xDist), yDist / abs(yDist));

	if (abs(xDist) + abs(yDist) < 5)
		loc = loc + pickAIPoint(dir, false);
	else
		loc = loc + pickAIPoint(dir, true);

	if (Point(abs(xDist), abs(yDist)) == Point(0, 1) || Point(abs(xDist), abs(yDist)) == Point(1, 0))
		return true;
	else {
		//Update loc in map grid
		try {
			if (loc > Point(0, 0) && loc < Point(63, 63)) {
				if (moveableCell(map[loc.x()][loc.y()].getLoc())) {
					map[monster->getLoc().x()][monster->getLoc().y()].setActor(NULL);
					monster->setLoc(loc);
					map[loc.x()][loc.y()].setActor(monster);
				}
			}
		}
		catch (int e) {
			OutputDebugString(to_string(e).c_str());
		}
		return false;
	}
}
Point GameEngine::pickAIPoint(Point dir, bool random) {
	int which = 0;
	if (!random) {
		which = rand() % 2;

		if (dir.x() != 0 && dir.y() != 0) {
			switch (which) {
			case 0:
				return Point(dir.x(), 0);
				break;
			case 1:
				return Point(0, dir.y());
				break;
			}
		}
		else
			return dir;
	}
	else {
		which = rand() % 4;

		switch (which) {
		case 0:
			return Point(1, 0);
			break;
		case 1:
			return Point(0, 1);
			break;
		case 2:
			return Point(-1, 0);
			break;
		case 3:
			return Point(0, -1);
			break;
		}
	}
}

void GameEngine::killMonster(Point loc) {
	//Kill off the monster
	map[loc.x()][loc.y()].setActor(NULL);

	int idx;
	for (idx = 0; idx < monsters.size(); idx++) {
		if (monsters[idx]->getLoc() == loc)
			break;
	}
	delete monsters[idx];
	monsters.erase(monsters.begin() + idx);
	lib.play("OnDeath");

	//Give them a chance to drop a pickup
	int which = rand() % pickupdefs.size();
	Pickup* p = new Pickup(pickupdefs[which], loc);
	map[loc.x()][loc.y()].setPickup(p);
	pickups.push_back(p);
}
void GameEngine::killHero() {
	deadHero = true;
	log.registerEvent("PRESS ESCAPE TO EXIT");
	lib.play("HeroOnDeath");
}
void GameEngine::addPickup(Point loc) {
	int idx = 0;
	bool itemAdded = false;

	//Add the new item to inventory log
	for (int i = 0; i < pickups.size(); i++) {
		if (pickups[i]->getLoc() == loc) {
			itemAdded = invLog.addItem(*pickups[i]);
			idx = i;
			break;
		}
	}

	//Add to log
	if (itemAdded) {
		log.registerEvent("Picked up a " + pickups[idx]->getPickupDef().getName() + "!");

		//Delete it from the game world
		map[loc.x()][loc.y()].setPickup(NULL);
		delete pickups[idx];
		pickups.erase(pickups.begin() + idx);
	}
	else
		log.registerEvent("Inventory full!");
}

string GameEngine::registerInventoryClick() {
	if ((lib.mouseLoc().x() == 22 || lib.mouseLoc().x() == 23) && lib.mouseLoc().y() >= 3 && lib.mouseLoc().y() <= 9) {
		if (!invLog.itemAlreadyEquipped(lib.mouseLoc()))
			return invLog.useItem(lib.mouseLoc());
		else if(invLog.getInvItemAtLoc(lib.mouseLoc()).getLoc() != Point(-1, -1)) {
			string event = invLog.getInvItemAtLoc(lib.mouseLoc()).getPickupDef().getName() + " is already equipped!";
			log.registerEvent(event.c_str());
		}
	}
	else if (lib.mouseLoc().x() >= 21 && lib.mouseLoc().x() <= 24 && lib.mouseLoc().y() == 15)
		invLog.openGear();
	return "";
}