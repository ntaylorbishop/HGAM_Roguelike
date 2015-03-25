#pragma once

#include "Point.h"
#include "ActorDef.h"
#include "MessageLog.h"

class Actor {
public:
	//STRUCTORS
	Actor();
	Actor(ActorDef def, Point loc, bool isHero);

	//GETTERS SETTERS
	int getHP();
	Point getLoc();
	ActorDef getActorDef();
	int getATK();
	void doDMG(int dmg);
	void setLoc(Point p);
	void setActorDef(ActorDef def);
	bool isHero();

	bool onDeath();

	//UTILITY
	bool instanceof(Actor a);
private:
	Point loc;
protected:
	int hp;
	bool hero;
	ActorDef def;
};

