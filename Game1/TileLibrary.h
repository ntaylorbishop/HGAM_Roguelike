#pragma once

#include "Point.h"

class TileLibrary
{
public:
	TileLibrary();
	~TileLibrary();

	void rendertile(int tile, Point p);
	Point tileres();
};

