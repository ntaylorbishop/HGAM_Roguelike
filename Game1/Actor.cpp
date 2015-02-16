#include "Actor.h"

//STRUCTORS
Actor::Actor(ActorDef def, Point loc) {
	this->def = def;
	this->hp = def.getMaxHP();
	this->loc = loc;
}
Actor::~Actor() {
}

//GETTERS SETTERS
int Actor::getHP() {
	return hp;
}
Point Actor::getLoc() {
	return loc;
}
ActorDef Actor::getActorDef() {
	return def;
}
void Actor::setHP(int hp) {
	this->hp = hp;
}
void Actor::setLoc(Point p) {
	this->loc = loc;
}
void Actor::setActorDef(ActorDef def) {
	this->def = def;
}

//OTHER
bool Actor::instanceof(Actor a) {
	if (this->def == a.getActorDef())
		return true;
	else
		return false;
}