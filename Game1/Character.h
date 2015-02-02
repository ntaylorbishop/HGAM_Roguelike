#pragma once

#include "Point.h"

class Character {
public:
	//Structors
	Character();
	Character(Point startPos);
	~Character();

	Point getPos();
private:
	Point pos;
};

