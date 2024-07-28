#pragma once
#include "game.h"

class ImageText {
public:
	Image image;
	Texture texture;
	Sprite sprite;
	int x, y;
	String file;

	ImageText() {};
	ImageText(String File, int X, int Y, bool white);
	~ImageText() {}
};

struct playerscoring {
	std::string name;
	int score;
};