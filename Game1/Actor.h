#pragma once

#include "Point.h"
#include "ActorDef.h"

class Actor {
public:
	//STRUCTORS
	Actor(ActorDef def, Point loc);
	~Actor();

	//GETTERS SETTERS
	int getHP();
	Point getLoc();
	ActorDef getActorDef();
	void setHP(int hp);
	void setLoc(Point p);
	void setActorDef(ActorDef def);

	//OTHER
	bool instanceof(Actor a);
private:
	int hp;
	Point loc;

	ActorDef def;
};

