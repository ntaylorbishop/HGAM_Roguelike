#include "MessageLog.h"

void MessageLog::init(TileLibrary* library) {
	this->lib = library;

	asciiMsgs.push_back(msgToASCII("Welcome to the Ruins of Amalor!"));
}
void MessageLog::registerEvent(string str) {
	asciiMsgs.push_back(msgToASCII(str));
}
void MessageLog::renderMsgs() {
	//Render background
	for (int x = 0; x < lib->res().x(); x++) {
		for (int y = lib->res().y() - 2; y < lib->res().y(); y++) {
			lib->rendertile(0x125, Point(x, y));
		}
	}

	//Render messages
	lib->tile_scale(2);
	Point pos(1, lib->res().y() - 4);
	if (asciiMsgs.size() >= 4) {
		for (std::vector<vector<int>>::size_type i = asciiMsgs.size() - 1; i != (std::vector<int>::size_type) - 1; i--) {
			renderMsg(pos, i);
		}
	}
	else if(asciiMsgs.size() < 4) {
		for (int i = asciiMsgs.size() - 1; i >= 0; i--) {
			renderMsg(pos, i);
		}
	}
	lib->tile_scale(1);
}

vector<int> MessageLog::msgToASCII(string str) {
	vector<int> chars;

	for (int i = 0; i < str.length(); i++)
		chars.push_back(static_cast<int>(str[i]));

	return chars;
}

void MessageLog::renderMsg(Point& pos, int idx) {
	pos.setx(1);
	for (int j = 0; j < asciiMsgs[idx].size(); j++) {
		lib->rendertile(asciiMsgs[idx][j], pos);
		pos.setx(pos.x() + 1);
	}
	pos.sety(pos.y() + 1);
}