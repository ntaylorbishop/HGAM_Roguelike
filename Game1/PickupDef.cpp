#include "PickupDef.h"

//STRUCTORS
PickupDef::PickupDef() {
	this->tile = 0;
	this->name = name;
	this->desc = "NULL";
	this->type = type;
	this->useEffect = [](){};
	this->removeEffect = [](){};
}
PickupDef::PickupDef(int tile, string name, int type, function<void()> useEffect) {
	this->tile = tile;
	this->name = name;
	this->desc = "NULL";
	this->type = type;
	this->useEffect = useEffect;
	this->removeEffect = [](){};
}
PickupDef::PickupDef(int tile, string name, string desc, int type, function<void()> useEffect, function<void()> removeEffect) {
	this->tile = tile;
	this->name = name;
	this->desc = desc;
	this->type = type;
	this->useEffect = useEffect;
	this->removeEffect = removeEffect;
}

//GETTERS / SETTERS
int PickupDef::getTile() {
	return tile;
}
string PickupDef::getName() {
	return name;
}
string PickupDef::getDESC() {
	return desc;
}
int PickupDef::getType() {
	return type;
}