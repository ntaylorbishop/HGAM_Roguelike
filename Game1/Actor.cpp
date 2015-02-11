#include "Actor.h"


Actor::Actor()
{
}
Actor::~Actor()
{
}

int Actor::getHP() {
	return hp;
}
int Actor::getMaxHP() {
	return maxhp;
}
int Actor::getATK() {
	return atk;
}
int Actor::getDEF() {
	return def;
}
Point Actor::getLoc() {
	return loc;
}

void Actor::setHP(int hp) {
	this->hp = hp;
}
void Actor::setDEF(int def) {
	this->def = def;
}
void Actor::changeLoc(Point p) {
	this->loc = p;
}
