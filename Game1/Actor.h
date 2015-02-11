#pragma once

#include "Point.h"

class Actor
{
public:
	Actor();
	~Actor();

	int getHP();
	int getMaxHP();
	int getATK();
	int getDEF();
	Point getLoc();
	
	void setHP(int hp);
	void setDEF(int def);
	void changeLoc(Point p);
private:
	int hp;
	int maxhp;
	int atk;
	int def;
	Point loc;
};

