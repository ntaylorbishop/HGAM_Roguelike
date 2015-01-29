#include "Cell.h"


//Structors
Cell::Cell() {
	x = 0;
	y = 0;
	type = 0;
}
Cell::Cell(int xCoord, int yCoord, int type) {
	x = xCoord;
	y = yCoord;
	this->type = type;
}

//Getters & Setters
int Cell::getXCoord() {
	return x;
}
int Cell::getYCoord() {
	return y;
}
int Cell::getCellType() {
	return type;
}
void Cell::setXCoord(int x) {
	this->x = x;
}
void Cell::setYCoord(int y) {
	this->y = y;
}
void Cell::setCellType(int type) {
	this->type = type;
}