#pragma once

#include <string>
#include "Dice.h"

using namespace std;

class ActorDef {
public:
	//STRUCTORS
	ActorDef();
	ActorDef(Dice atk, int def, int maxhp, int tile, string desc);

	//GETTERS SETTERS
	Dice actorATK();
	int getDEF();
	int getMaxHP();
	int getTile();
	string getDESC();

	void setATK(Dice atk);
	void setDEF(int def);
	void setMaxHP(int maxhp);
	void setTile(int tile);
	void setDESC(string str);

	//OTHER
	bool operator==(const ActorDef &other) const {
		if (this->atk == other.atk && this->def == other.def && this->maxhp == other.maxhp && this->tile == other.tile && this->desc == other.desc)
			return true;
		else
			return false;
	}
	bool operator!=(const ActorDef &other) const {
		return !(*this == other);
	}
private:
	Dice atk;
	int def;
	int maxhp;
	int tile;
	string desc;
};

