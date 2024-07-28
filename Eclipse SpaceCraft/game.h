#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace sf;

class object {
public:
	float x{}, y{}, dx{}, dy{}; // координаты появления, ускорение по х и у,
	float speed; // скорость
	float fullspeed = 0;
	int w, h, health; // направление, ширина, высота и здоровье
	bool life;
	Image image;
	Texture texture;
	Sprite sprite;
	String f;
	String Name;

	object(){};
	object(float X, float Y, int W, int H, String F, String name);
	~object(){}
	
	virtual void update(float time)=0;
};

class ship : public object {
public:
	int dir;
	int score;

	ship() {};
	ship(float X, float Y, int W, int H, String F, String name);
	~ship(){}

	void update(float time);
	void stop();
	void control();
};

class meteor : public object {
public:
	meteor() {};
	meteor(float X, float Y, int W, int H, String F, String name);
	~meteor() {}

	void update(float time);
};

class boss : public object {
public:

	boss() {};
	boss(float X, float Y, int W, int H, String F, String name);
	~boss() {}

	void update(float time);
};

class bullet : public object {
public:
	int direction;
	bullet() {};
	bullet(float X, float Y, int W, int H, String F, int dir, String name);
	~bullet() {}

	void update(float time);
};

class bonus : public object{
public:
	bonus() {}
	bonus(float X, float Y, int W, int H, String F, String name);
	~bonus() {}

	void update(float times);
};