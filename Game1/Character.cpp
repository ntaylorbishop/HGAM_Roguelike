#include "Character.h"


Character::Character() {
	xPos = 0;
	yPos = 0;
}
Character::Character(int startXPos, int startYPos) {
	xPos = startXPos;
	yPos = startYPos;
}


Character::~Character() {
}

void Character::moveChar(int dir) {
	if (dir == 0 && xPos > 0)
		xPos--;
	else if (dir == 1 && yPos > 0)
		yPos--;
	else if (dir == 2 && xPos < 24)
		xPos++;
	else if (dir == 3 && yPos < 18)
		yPos++;
}

int Character::getX() {
	return xPos;
}

int Character::getY() {
	return yPos;
}