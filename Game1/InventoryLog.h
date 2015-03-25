#pragma onc
#ifndef INVENTORYLOG_H
#define INVENTORYLOG_H
#include <vector>
#include <string>
#include <Windows.h>

#include "TileLibrary.h"
#include "Point.h"
#include "MessageLog.h"
#include "Pickup.h"
#include "Hero.h"

class InventoryLog
{
public:
	void init(TileLibrary* library, Hero* hero);
	bool addItem(Pickup item);
	void renderInventory();
	string useItem(Point loc);

	int idxFromPoint(Point loc);
	bool isInventoryFull();
	void renderText(Point start, string text);

	int getItemType(Point loc);

	//Gear
	void openGear();
	void closeGear();
	bool isGearOpen();
	void renderGear();
	Point getExitBtn();
	void renderGearSlot(Point loc, int tile);
	void renderGearSlot(Point loc, Pickup p);

	Pickup unequipGear(Point loc);
	Pickup dropItem(Point loc);
	bool itemAlreadyEquipped(Point loc);
	Pickup getInvItemAtLoc(Point loc);

	template<typename Func>
	void loop_portion(Point start, Point end, Func f) {
		for (int x = start.x(); x < end.x(); x++) {
			for (int y = start.y(); y < end.y(); y++) {
				f(Point(x, y));
			}
		}
	}
private:
	TileLibrary* lib;
	vector<Pickup> inventory;
	vector<Pickup> gear;
	Hero* hero;
	int maxSize;
	bool gearOpen;
	int gearBoxSize;
	int numGear;
	int highlight_color;
	vector<int> gearSlotIcons;
	vector<Point> gearSlots;
};

#endif