#include "Tile.h"


//Structors
Tile::Tile() {
	coords.setCoords(0, 0);
	type = 0;
	tile = 0;
}
Tile::Tile(Point p, int type, int tile) {
	coords = p;
	this->type = type;
	this->tile = tile;
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
void Tile::setCoords(Point p) {
	coords = p;
}
void Tile::setTileType(int type) {
	this->type = type;
}
void Tile::setTile(int tile) {
	this->tile = tile;
}