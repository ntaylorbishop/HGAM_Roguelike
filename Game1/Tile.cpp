#include "Tile.h"


//Structors
Tile::Tile() {
	coords.setCoords(0, 0);
	type = 0;
	tile = 0;
	zone = 0;
}
Tile::Tile(Point p, int type, int tile, int zone) {
	coords = p;
	this->type = type;
	this->tile = tile;
	this->zone = zone;
}

//Getters & Setters
Point Tile::getCoords() {
	return coords;
}
int Tile::getTileType() {
	return type;
}
int Tile::getTile() {
	return tile;
}
int Tile::getZone() {
	return zone;
}
void Tile::setCoords(Point p) {
	coords = p;
}
void Tile::setTileType(int type) {
	this->type = type;
}
void Tile::setTile(int tile) {
	this->tile = tile;
}
void Tile::setZone(int zone) {
	this->zone = zone;
}