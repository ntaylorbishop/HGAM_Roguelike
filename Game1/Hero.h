#pragma once
#ifndef HERO_H
#define HERO_H
#include <vector>

#include "Actor.h"
#include "Dice.h"

class Hero: public Actor {
public:
	Hero(ActorDef def, Point loc, bool isHero) : Actor(def, loc, isHero) {};
	void setATK(Dice atk);
	void setDEF(int def);
	void setHP(int hp);
	void setMaxHP(int maxhp);
private:
};

#endif
