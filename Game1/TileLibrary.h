#pragma once

#include <stddef.h>

#include "tilelib.h"
#include "Point.h"

class TileLibrary
{
public:
	TileLibrary();
	~TileLibrary();

	void init(char *windowtitle, int width, int height, char *name, int tilesz = 32, int numtex = 1);
	void framestart();
	void rendertile(int tile, Point loc);

	Point res();

	void tile_color(int col = 0xFFFFFFFF);
	void tile_scale(int sc = 1);
	void tile_rotation(int rot = 0);
	void tile_toggleflip();

	bool keydown(char *key);
	bool keywentdown(char *key);

	bool buttondown(int button = 1);
	bool buttonwentdown(int button = 1);

	Point mouseLoc();

	void play(char *sfs_filename);
};

