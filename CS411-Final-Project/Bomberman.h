#pragma once
#include "Sprite.h"
#include "KeyboardManager.h"

static const int MOVE_STEP = 4;

class Bomberman : public Sprite
{
	int _numBoom;
	bool _isAlive;


public:

	Bomberman(const string& name);
	~Bomberman() {};

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();

	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void put_boom();
};