#pragma once
#include "Sprite.h"
#include "KeyboardManager.h"

static const int MOVE_STEP = 4;

class Bomb;

/* ======================================================================
* Bomberman
* =================================================================== */

class Bomberman : public Sprite
{
	int _numBomb;
	bool _isAlive;
	list<Bomb> _bombs;

public:

	Bomberman(const string& name);
	~Bomberman() {};

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();

	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void put_bomb();
};

/* ======================================================================
* Bomb
* =================================================================== */

class Bomb : public Sprite
{
	friend class Bomberman;
private:
	long long _count_down;
	long long _explostion_animation_counter;
	int _power;
	bool _removable;

	void draw_center_flame(int const & animation_state);
	void draw_vertical_flame(int const & animation_state);
	void draw_horizontal_flame(int const & animation_state);
public:
	Bomb(Vector2 const & position);
	~Bomb();

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};