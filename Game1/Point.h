#pragma once

/*
 * Name: Point
 * Description: Holds an x,y point (in tile orientation)
 *
 */
class Point
{
public:
	//Structors
	Point();
	Point(int x, int y);

	//Getters / Setters
	int x();
	int y();
	void setx(int x);
	void sety(int y);
	void setCoords(int x, int y);
private:
	int xCoord;
	int yCoord;
};

