#include <Windows.h>

#include "Cell.h"

//Structors
Cell::Cell() {
	loc = Point(0, 0);
	type = 0;
	tile = 0;
	zone = 0;
}
Cell::Cell(Point p, int type, int tile, int zone) {
	loc = p;
	this->type = type;
	this->tile = tile;
	this->zone = zone;
}

//Getters & Setters
Point Cell::getLoc() {
	return loc;
}
int Cell::getCellType() {
	return type;
}
int Cell::getTile() {
	return tile;
}
int Cell::getZone() {
	return zone;
}
Actor* Cell::getActor() {
	return a;
}
Pickup* Cell::getPickup() {
	return p;
}

void Cell::setLoc(Point p) {
	loc = p;
}
void Cell::setTileType(int type) {
	if (type < 0 || type > 4)
		OutputDebugString("TILE TYPE IS NOT SET PROPERLY");
	else
		this->type = type;
}
void Cell::setTile(int tile) {
	this->tile = tile;
}
void Cell::setZone(int zone) {
	this->zone = zone;
}
void Cell::setActor(Actor* a) {
	this->a = a;
}
void Cell::setPickup(Pickup* p) {
	this->p = p;
}