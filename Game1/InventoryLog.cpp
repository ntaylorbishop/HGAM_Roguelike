#include "InventoryLog.h"

void InventoryLog::init(TileLibrary* library, Hero* hero) {
	this->lib = library;
	this->hero = hero;
	maxSize = 14;
	gearBoxSize = 15;
	gearOpen = false;
	highlight_color = 0x0A0091FF;
	numGear = 9;
	gearSlots = { Point(0, 0), Point(3, 0), Point(0, 2), Point(3, 2), Point(0, 4), Point(3, 4), Point(0, 6), Point(3, 6) };

	for (int i = 0; i < maxSize; i++)
		inventory.push_back(Pickup());
	for (int i = 0; i < numGear; i++)
		gear.push_back(Pickup());

	gearSlotIcons = { 0x2DD, 0x337, 0x2D0, 0x2E7, 0x2E0, 0x3D0, 0x250, 0x2C0 };
}
bool InventoryLog::addItem(Pickup item) {
	if (isInventoryFull())
		return false;
	else {
		lib->play("OnPickup");
		for (int i = 0; i < inventory.size(); i++) {
			if (inventory[i].getLoc() == Point(-1, -1)) {
				inventory[i] = item;
				return true;
			}
		}
	}
}
void InventoryLog::renderInventory() {
	renderGear();

	//Render background
	for (int x = lib->res().x() - 4; x < lib->res().x(); x++) {
		for (int y = 0; y < lib->res().y() - 2; y++) {
			lib->rendertile(0x125, Point(x, y));
			tl_color(0x00000040);
			lib->rendertile(0x125, Point(x, y));
			tl_color(0xFFFFFFFF);
		}
	}

	//Render items
	int idx = 0;
	for (int y = 3; y < maxSize / 2 + 3; y++) {
		for (int x = lib->res().x() - 3; x < lib->res().x() - 1; x++) {
			lib->rendertile(0x13D, Point(x, y));
			if (lib->mouseLoc() == Point(x, y) && inventory[idxFromPoint(lib->mouseLoc())].getLoc() != Point(-1, -1) && !gearOpen) {
				tl_color(0xFF000040);
				lib->rendertile(0x13D, Point(x, y));
			}
			tl_color(0xFFFFFFFF);
			if (idx <= inventory.size() - 1 && !inventory.empty()) {
				lib->rendertile(inventory[idx].getPickupDef().getTile(), Point(x, y));
				idx++;
			}
		}
	}

	//RENDER TEXT
	//Render HP
	lib->tile_scale(3);
	Point pos(lib->res().x() - 11, 1);
	string str = "HP:" + to_string(hero->getHP()) + "/" + to_string(hero->getActorDef().getMaxHP());
	renderText(pos, str);
	//Render ATK
	lib->tile_scale(3);
	pos = Point(lib->res().x() - 11, 2);
	str = "ATK: " + hero->getActorDef().actorATK().to_str();
	renderText(pos, str);
	//Render DEF
	pos = Point(lib->res().x() - 11, 3);
	str = "DEF:" + to_string(hero->getActorDef().getDEF());
	renderText(pos, str);
	//Render XP
	pos = Point(lib->res().x() - 11, 4);
	str = "XP: 99/100";
	renderText(pos, str);

	//Render equipment text
	pos = Point(lib->res().x() - 11, 45);
	str = "INVENTORY";
	if (lib->mouseLoc().x() >= (lib->res().x() - 11) && lib->mouseLoc().x() <= (lib->res().x() - 2) && lib->mouseLoc().y() == 45 && !gearOpen)
		tl_color(highlight_color);
	renderText(pos, str);
	tl_color(0xFFFFFFFF);

	lib->tile_scale(1);
}
string InventoryLog::useItem(Point loc) {
	int idx = idxFromPoint(loc);
	int itemType = inventory[idx].getPickupDef().getType();
	string itemUsed = inventory[idx].getPickupDef().getName();

	if (itemType != 0 && inventory[idx].getLoc() != Point(-1, -1)) {
		lib->play("OnUse");
		gear[itemType] = inventory[idx];
		gear[itemType].getPickupDef().useEffect();
		inventory[idx] = Pickup();
	}
	else {
		lib->play("OnUse");
		inventory[idx].getPickupDef().useEffect();
		inventory[idx] = Pickup();
	}

	return itemUsed;
}

int InventoryLog::idxFromPoint(Point loc) {
	loc = loc - Point(22, 3);
	if (loc == Point(0, 0)) return 0;
	else if (loc == Point(1, 0)) return 1;
	else if (loc == Point(0, 1)) return 2;
	else if (loc == Point(1, 1)) return 3;
	else if (loc == Point(0, 2)) return 4;
	else if (loc == Point(1, 2)) return 5;
	else if(loc == Point(0, 3)) return 6;
	else if(loc == Point(1, 3)) return 7;
	else if(loc == Point(0, 4)) return 8;
	else if(loc == Point(1, 4)) return 9;
	else if(loc == Point(0, 5)) return 10;
	else if(loc == Point(1, 5)) return 11;
	else if(loc == Point(0, 6)) return 12;
	else if(loc == Point(1, 6)) return 13;
	else return -1;
}
bool InventoryLog::isInventoryFull() {
	int trueSize = 0;
	for (int i = 0; i < inventory.size(); i++) {
		if (inventory[i].getLoc() != Point(-1, -1))
			trueSize++;
	}
	if (trueSize == maxSize)
		return true;
	else
		return false;
}
void InventoryLog::renderText(Point start, string text) {
	for (int i = 0; i < text.length(); i++) {
		lib->rendertile(static_cast<int>(text[i]), start);
		start = start + Point(1, 0);
	}
}

int InventoryLog::getItemType(Point loc) {
	return inventory[idxFromPoint(loc)].getPickupDef().getType();
}

void InventoryLog::openGear() {
	gearOpen = true;
}
void InventoryLog::closeGear() {
	gearOpen = false;
}
bool InventoryLog::isGearOpen() {
	return gearOpen;
}
Point InventoryLog::getExitBtn() {
	return Point(lib->res().x() / 2 - gearBoxSize / 2, lib->res().y() / 2 - gearBoxSize / 2);
}
void InventoryLog::renderGear() {
	//DEBUG

	//Render equipment --Done first to fade out background
	if (gearOpen) {
		tl_scale(1);
		Point start(lib->res().x() / 2 - gearBoxSize / 2, lib->res().y() / 2 - gearBoxSize / 2);
		Point end(lib->res().x() / 2 + gearBoxSize / 2, lib->res().y() / 2 + gearBoxSize / 2);
		OutputDebugString(lib->mouseLoc().to_str().c_str());
		//Gear background
		tl_color(0x3B3B3BFF);
		for (int x = 0; x < gearBoxSize - 1; x++) 
			lib->rendertile(0x1120, Point(start.x() + x, start.y()));
		loop_portion(start + Point(0, 1), end, [&](Point p) {
			lib->rendertile(0x13E, Point(p.x(), p.y()));
		});
		for (int x = 0; x < gearBoxSize - 1; x++)
			lib->rendertile(0x1120, Point(start.x() + x, end.y()));
		tl_color(0xFFFFFFFF);

		//Close button
		char closeBtn = 'x';
		if (lib->mouseLoc() == start) tl_color(highlight_color);
		lib->rendertile(static_cast<int>(closeBtn), start);
		tl_color(0xFFFFFFFF);

		//Title text
		Point gearStart(lib->res().x() / 2 - 2, start.y());
		renderText(gearStart, "Gear");

		//Gear & Gear slots
		Point slotStart(lib->res().x() / 2 - 2, start.y() + 3);

		for (int i = 1; i < numGear; i++) {
			if (gear[i].getLoc() == Point(-1, -1))
				renderGearSlot(slotStart + gearSlots[i - 1], gearSlotIcons[i - 1]);
			else {
				lib->rendertile(0x13D, slotStart + gearSlots[i - 1]);
				lib->rendertile(gear[i].getPickupDef().getTile(), slotStart + gearSlots[i - 1]);
			}
		}
		tl_scale(1);

		//Exit gear
		if (tl_buttonwentdown(1) && lib->mouseLoc() == start)
			closeGear();
	}
}

void InventoryLog::renderGearSlot(Point loc, int tile) {
	tl_color(0xFFFFFFFF);
	lib->rendertile(0x13D,  loc);
	tl_color(0xFFFFFF60);
	lib->rendertile(tile, loc);
	tl_color(0xFFFFFFFF);
}
void InventoryLog::renderGearSlot(Point loc, Pickup p) {
	lib->rendertile(p.getPickupDef().getTile(), loc);
}

Pickup InventoryLog::unequipGear(Point loc) {
	OutputDebugString("herpderp");
	Point start(lib->res().x() / 2 - gearBoxSize / 2, lib->res().y() / 2 - gearBoxSize / 2);
	Point slotStart(lib->res().x() / 2 - 2, start.y() + 3);
	vector<Point> gearSlots = { Point(0, 0), Point(3, 0), Point(0, 2), Point(3, 2), Point(0, 4), Point(3, 4), Point(0, 6), Point(3, 6) };
	Pickup p;

	for (int i = 0; i < 8; i++) {
		if (loc == slotStart + gearSlots[i]) {
			p = gear[i + 1];
			gear[i + 1] = Pickup();
			p.getPickupDef().removeEffect();
			for (int j = 0; j < inventory.size(); j++) {
				if (inventory[j].getLoc() == Point(-1, -1)) {
					inventory[j] = p;
					break;
				}
			}
		}
	}
	return p;
}
Pickup InventoryLog::dropItem(Point loc) {
	int idx = idxFromPoint(loc);
	Pickup p = inventory[idx];
	if (idx != -1)
		inventory[idx] = Pickup();
	return p;
}

bool InventoryLog::itemAlreadyEquipped(Point loc) {
	Pickup p = getInvItemAtLoc(loc);
	OutputDebugString(p.getPickupDef().getName().c_str());
	bool b = false;
	for (int i = 1; i < 8; i++) {
		if (p.getPickupDef().getName() == gear[i + 1].getPickupDef().getName())
			b = true;
	}
	return b;
}
Pickup InventoryLog::getInvItemAtLoc(Point loc) {
	Pickup p;
	int idx = idxFromPoint(loc);
	p = inventory[idx];
	return p;
}