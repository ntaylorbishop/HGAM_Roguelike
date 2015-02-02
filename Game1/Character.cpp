#include "Character.h"


Character::Character() {
	pos.setx(0);
	pos.sety(0);
}
Character::Character(Point startPos) {
	pos = startPos;
}
Character::~Character() {
}

Point Character::getPos() {
	return pos;
}