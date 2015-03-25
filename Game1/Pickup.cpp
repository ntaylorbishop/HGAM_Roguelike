#include "Pickup.h"

//STRUCTORS
Pickup::Pickup() {
	this->def = PickupDef();
	this->loc = Point(-1, -1);
}
Pickup::Pickup(PickupDef def, Point loc) {
	this->def = def;
	this->loc = loc;
}

//GETTERS / SETTERS
PickupDef Pickup::getPickupDef() {
	return def;
}
Point Pickup::getLoc() {
	return loc;
}
void Pickup::setLoc(Point nLoc) {
	loc = nLoc;
}
