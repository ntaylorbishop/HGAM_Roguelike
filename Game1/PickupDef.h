#pragma once

#include <functional>
#include <string>

using namespace std;

class PickupDef {
public:
	//STRUCTORS
	PickupDef();
	PickupDef(int tile, string name, int type, function<void()> useEffect);
	PickupDef(int tile, string name, string desc, int type, function<void()> useEffect, function<void()> removeEffect);

	//GETTERS / SETTERS
	int getTile();
	string getName();
	string getDESC();
	int getType();

	function <void()> useEffect;
	function <void()> removeEffect;

	bool operator==(const PickupDef &other) const {
		if (this->name == other.name)
			return true;
		else
			return false;
	}
	bool operator!=(const PickupDef &other) const {
		return !(*this == other);
	}
private:
	int tile;
	string name;
	string desc;
	int type; //0 Potion, 1 Head, 2 Neck, 3 Chest, 4 Hand, 5 feet, 6 tomb, 7 sword, 8 shield
};

