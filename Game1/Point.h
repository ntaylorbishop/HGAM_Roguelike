#pragma once

/*
 * Name: Point
 * Description: Holds an x,y point (in tile orientation)
 *
 */
class Point {
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

	Point& operator=(const Point &rhs) {
		if (this == &rhs)
			return *this;
		else {
			xCoord = rhs.xCoord;
			yCoord = rhs.yCoord;
			return *this;
		}
	}
	friend Point operator+(const Point &p1, const Point &p2);
	friend Point operator-(const Point &p1, const Point &p2);

	Point& operator/(int n) {
		xCoord = xCoord / n;
		yCoord = yCoord / n;
		return *this;
	}
private:
	int xCoord;
	int yCoord;
};
