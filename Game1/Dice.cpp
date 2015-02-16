#include "Dice.h"

Dice::Dice() {
	this->sides = -1;
	this->rolls = -1;
}
Dice::Dice(int sides, int rolls) {
	this->sides = sides;
	this->rolls = rolls;
}
int Dice::rollDice() {
	int sum = 0;
	for (int i = 0; i < rolls; i++)
		sum += rand() % sides + 1;
	return sum;
}
