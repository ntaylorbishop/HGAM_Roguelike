#pragma once

#include <vector>
#include <string>
#include <Windows.h>

#include "TileLibrary.h"
#include "Point.h"

class MessageLog {
public:

	void init(TileLibrary* library);
	void registerEvent(string str);
	void renderMsgs();
	vector<int> msgToASCII(string msg);

	void renderMsg(Point& pos, int idx);
private:
	TileLibrary* lib;
	vector<string> msgs;
	vector<vector<int>> asciiMsgs;
};

