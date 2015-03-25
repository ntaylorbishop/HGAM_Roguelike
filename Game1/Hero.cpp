#include "Hero.h"

void Hero::setATK(Dice atk) {
	this->def.setATK(atk);
}
void Hero::setDEF(int def) {
	this->def.setDEF(def);
}
void Hero::setHP(int hp) {
	if (hp > getActorDef().getMaxHP())
		this->hp = getActorDef().getMaxHP();
	else
		this->hp = hp;
}
void Hero::setMaxHP(int maxhp) {
	this->def.setMaxHP(maxhp);
}