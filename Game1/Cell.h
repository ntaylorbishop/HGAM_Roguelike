#pragma once

#include <string>

class Cell {
public:
	//Structors

	/* Default constructor
	 * Description: Initializes a new cell object. Defaults the x and y coordinates to (0, 0) and type to dummy cell
	 */
	Cell();

	/* Constructor
	 * Description: Initializes a new cell object. Sets the x and y coordinates, and type of cell
	 * @Params:
	 *		xCoord: x coordinate of the cell
	 *		yCoord: y coordinate of the cell
	 *		type: 0 for dummy cell, 1 for floor tile, 2 for wall
	 */
	Cell(int xCoord, int yCoord, int type);

	//Getters Setters
	int getXCoord();
	int getYCoord();
	int getCellType();
	void setXCoord(int x);
	void setYCoord(int y);
	void setCellType(int type);
private:
	int x;
	int y;
	int type;
};

