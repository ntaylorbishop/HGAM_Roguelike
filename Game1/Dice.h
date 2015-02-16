#pragma once

#include <cstdlib>

using namespace std;
class Dice
{
public:
	Dice();
	Dice(int sides, int rolls);
	int rollDice();
	bool operator==(const Dice &other) const {
		if (this->sides == other.sides && this->rolls == other.rolls)
			return true;
		else
			return false;
	}
	bool operator!=(const Dice &other) const {
		return !(*this == other);
	}
private:
	int sides;
	int rolls;
};

