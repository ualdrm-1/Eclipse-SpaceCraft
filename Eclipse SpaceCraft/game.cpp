#include "game.h"

object::object(float X, float Y, int W, int H, String F, String name) {
	x = X, y = Y, w = W, h = H, Name = name; f = F;
	speed = 0; health = 1; dx = 0; dy = 0;
	life = 1;
	image.loadFromFile(f);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

ship::ship(float X, float Y, int W, int H, String F, String name) {
	score = 0; life = 1;
	f = F; name = Name;
		image.loadFromFile(f);
		image.createMaskFromColor(Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X, y = Y;
		sprite.setTextureRect(IntRect(0, 0, W, H));
}

boss::boss(float X, float Y, int W, int H, String F, String name) {
	f = F; name = Name; speed = 0.1;
	life = 1;
	health = 10;
	image.loadFromFile(f);
	image.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = X, y = Y;
	sprite.setTextureRect(IntRect(0, 0, W, H));
}

bullet::bullet(float X, float Y, int W, int H, String F, int dir, String name) {
	x = X;
	y = Y;
	life = 1;
	direction = dir;
	speed = 0.3;
	w = W;
	h = H;
	f = F;
	Name = name;
	image.loadFromFile(f);
	image.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0,0, W,H));
}

meteor::meteor(float X, float Y, int W, int H, String F, String name) {
	f = F; Name = name;
	if (Name == "asteroid") {
		image.loadFromFile(f);
		image.createMaskFromColor(Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, W, H));
		dx = 0.1;
	}
}

void ship::update(float time) {
	
control();
	switch (dir) {
	case 0: dx = speed; dy = 0; break;
	case 1: dx = -speed; dy = 0;   break;
	case 2: dx = 0; dy = speed;   break;
	case 3: dx = 0; dy = -speed;   break;
	}
	x += dx * time;
	y += dy * time;
	
	speed = 0;
	sprite.setPosition(x, y);
	stop();
}

void ship::stop() {
	if (sprite.getPosition().x < 0) {
		sprite.setPosition(0, sprite.getPosition().y);
	}
	else if (sprite.getPosition().x > 1880) {
		sprite.setPosition(1880, sprite.getPosition().y);
	}
	if (sprite.getPosition().y < 0) {
		sprite.setPosition(sprite.getPosition().x, 0);
	}
	else if (sprite.getPosition().y > 1000) {
		sprite.setPosition(sprite.getPosition().x, 1000);
	}
}

void ship:: control() {
	if (life==1) {
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			//player.sprite.rotate(-0.4);
			dir = 1;speed = fullspeed+0.1;//направление влево
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			//player.sprite.rotate(0.4);
			dir = 0;speed = fullspeed+0.3;//направление вправо
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			dir = 3; speed = fullspeed + 0.2;//направление вниз
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			dir = 2; speed = fullspeed + 0.2;//направление вверх
		}
	}
}

void boss::update(float times) {
	x -= 0.05 * times;
	sprite.setPosition(x, y);
}

void bullet::update(float time) {
	switch (direction) {
		case 0: dx = speed; dy = 0; break;
		case 1: dx = speed; dy = 0; break;
		case 2: dx = speed; dy = 0;	break;
		case 3: dx = speed; dy = 0; break;
	}
	x += dx * time;
	y += dy * time;
	sprite.setPosition(x+150,y+35);
}

void meteor::update(float times) {
	x += -dx * times;
	y += dy * times;
	srand(time(0));
	char rotation = rand() % 3 - 1;
	if (rotation == -1) {
		sprite.rotate(0.1);
	}
	else if (rotation == 1) {
		sprite.rotate(-0.1);
	}
	if (rotation == 0) {
		sprite.rotate(0.1);
	}
	sprite.setPosition(x, y);
}

bonus::bonus(float X, float Y, int W, int H, String F, String name) {
	x = X; y = Y; life = 1; w = W; h = H; f = F; Name = name;
	image.loadFromFile(f);
	image.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, W, H));
}

void bonus::update(float times) {
	x -= 0.1 * times;
	sprite.setPosition(x, y);
}