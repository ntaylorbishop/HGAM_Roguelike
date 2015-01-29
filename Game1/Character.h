#pragma once
class Character {
public:
	//Structors
	Character();
	Character(int startXPos, int startYPos);
	~Character();

	//Member functions

	/* Name: moveChar
	 * Description: Moves character left, right, up, or down one tile
	 * @Params: int dir - 0 for left, 1 for up, 2 for right, 3 for down
	 */
	void moveChar(int dir);

	int getX();
	int getY();
private:
	int xPos = 0;
	int yPos = 0;
};

