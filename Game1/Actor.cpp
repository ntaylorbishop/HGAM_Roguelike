#include "Actor.h"

//STRUCTORS
Actor::Actor() {

}
Actor::Actor(ActorDef def, Point loc, bool isHero) {
	this->def = def;
	this->hp = def.getMaxHP();
	this->loc = loc;
	this->hero = isHero;
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
int Actor::getATK() {
	return def.actorATK().rollDice();
}
void Actor::doDMG(int dmg) {
	if (dmg > 0)
		hp = hp - dmg;
}
void Actor::setLoc(Point p) {
	this->loc = p;
}
void Actor::setActorDef(ActorDef def) {
	this->def = def;
}
bool Actor::isHero() {
	return hero;
}

bool Actor::onDeath() {
	if (hp <= 0)
		return true;
	else
		return false;
}

//UTILITY
bool Actor::instanceof(Actor a) {
	if (this->def == a.getActorDef())
		return true;
	else
		return false;
}

/*Point heroLoc = hero->getLoc();
	int xDist = heroLoc.x() - loc.x();
	int yDist = heroLoc.y() - loc.y();
	int which = 0;

	Point dir(0, 0);

	if (xDist == 0 && yDist == 0)
		dir = Point(0, 0);
	else if (xDist == 0 && yDist != 0)
		dir = Point(0, yDist / abs(yDist));
	else if (xDist != 0 && yDist == 0)
		dir = Point(xDist / abs(xDist), 0);
	else
		dir = Point(xDist / abs(xDist), yDist / abs(yDist));

	if (abs(xDist) + abs(yDist) < 4) {
		if (dir.x() < 0 && dir.y() < 0) {
			which = rand() % 1;
			if (which == 0)
				this->loc = this->loc + Point(-1, 0);
			else if (which == 1)
				this->loc = this->loc + Point(0, -1);
			else {
				OutputDebugString("Not working");
				this->loc = this->loc + Point(0, 0);
			}
		}
		else if (dir.x() > 0 && dir.y() > 0) {
			which = rand() + 1;
			if (which == 0)
				this->loc = this->loc + Point(1, 0);
			else if (which == 1)
				this->loc = this->loc + Point(0, 1);
			else {
				OutputDebugString("Not working");
				this->loc = this->loc + Point(0, 0);
			}

		}
		else
			this->loc = this->loc + dir;
	}
	else {
		which = rand() % 3;

		if (which == 0)
			this->loc = this->loc + Point(1, 0);
		else if (which == 1)
			this->loc = this->loc + Point(0, 1);
		else if (which == 2)
			this->loc = this->loc + Point(-1, 0);
		else if (which == 3)
			this->loc = this->loc + Point(0, -1);
		else {
			OutputDebugString("Not working");
			this->loc = this->loc + Point(0, 0);
		}
		}*/