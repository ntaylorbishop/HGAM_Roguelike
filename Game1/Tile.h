#pragma once

#include "Point.h"

class Tile {
public:

	//Structors

	/* Default constructor
	 * Description: Initializes a new Tile object. Defaults the x and y coordinates to (0, 0) and type to dummy Tile
	 */
	Tile();

	/* Constructor
	 * Description: Initializes a new Tile object. Sets the x and y coordinates, and type of Tile
	 * @Params:
	 *		xCoord: x coordinate of the Tile
	 *		yCoord: y coordinate of the Tile
	 *		type: 0 for dummy Tile, 1 for floor tile, 2 for wall, 3 for Character
	 *		tile: The tile to draw
	 */
	Tile(Point p, int type, int tile);

	//Getters Setters
	Point getCoords();
	int getTileType();
	int getTile();
	void setCoords(Point p);
	void setTileType(int type);
	void setTile(int tile);
private:
	Point coords;
	int type;
	int tile;
};

