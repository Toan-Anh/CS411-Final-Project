#pragma once
#include"Sprite.h"


static const int MOVE_STEP = 4;

class Boomberman : public Sprite
{
	int _numBoom;
	bool _isAlive;


public:

	Boomberman(const string& name);
	~Boomberman() {};
	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void put_boom();


};