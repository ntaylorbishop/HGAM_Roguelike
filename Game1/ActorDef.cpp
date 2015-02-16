#include "ActorDef.h"


//STRUCTORS
ActorDef::ActorDef() {
	def = 0;
	maxhp = 0;
	tile = 0;
	desc = "";
}
ActorDef::ActorDef(Dice atk, int def, int maxhp, int tile, string desc) {
	this->atk = atk;
	this->def = def;
	this->maxhp = maxhp;
	this->tile = tile;
	this->desc = desc;
}

//GETTERS SETTERS
Dice ActorDef::getATK() {
	return atk;
}
int ActorDef::getDEF() {
	return def;
}
int ActorDef::getMaxHP() {
	return maxhp;
}
int ActorDef::getTile() {
	return tile;
}
string ActorDef::getDESC() {
	return desc;
}

void ActorDef::setATK(Dice atk) {
	this->atk = atk;
}
void ActorDef::setDEF(int def) {
	this->def = def;
}
void ActorDef::setMaxHP(int maxhp) {
	this->maxhp = maxhp;
}
void ActorDef::setTile(int tile) {
	this->tile = tile;
}
void ActorDef::setDESC(string str) {
	this->desc = str;
}