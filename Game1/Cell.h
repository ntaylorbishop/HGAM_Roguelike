#pragma once

#include "Point.h"
#include "Actor.h"

class Cell {
public:

	//Structors

	/* Default constructor
	 * Description: Initializes a new Tile object. Defaults the x and y coordinates to (0, 0) and type to dummy Tile
	 */
	Cell();

	/* Constructor
	 * Description: Initializes a new Tile object. Sets the x and y coordinates, and type of Tile
	 * @Params:
	 *		xCoord: x coordinate of the Tile
	 *		yCoord: y coordinate of the Tile
	 *		type: 0 for dummy Tile, 1 for floor tile, 2 for wall, 3 for Character
	 *		tile: The tile to draw
	 */
	Cell(Point p, int type, int tile, int zone);

	//Getters Setters
	Point getLoc();
	int getCellType();
	int getTile();
	int getZone();
	Actor* getActor();
	void setLoc(Point p);
	void setTileType(int type);
	void setTile(int tile);
	void setZone(int zone);
	void setActor(Actor* a);
private:
	Point loc;
	int type;
	int tile;
	int zone;
	Actor* a = NULL;
};

