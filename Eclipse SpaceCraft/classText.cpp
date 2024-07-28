#include "ClassTexts.h"

ImageText::ImageText(String File, int X, int Y, bool white) {
	file = File; x = X; y = Y;
	image.loadFromFile(file);
	if (white == true) {
		image.createMaskFromColor(Color(255, 255, 255));
	}
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}