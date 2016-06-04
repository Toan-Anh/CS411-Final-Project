#pragma once
#include "Sprite.h"
#include "KeyboardManager.h"
#include "SceneManager.h"
#include "Scene_GameOver.h"
#include "GameMap.h"
#include "Global.h"

static const int MOVE_STEP = 32;

class Bomb;

/* ======================================================================
* Bomberman
* =================================================================== */

class Bomberman : public Sprite
{
	int _numBomb;
	bool _isAlive;
	list<Bomb*> _bombs;
	GameMap& _map;

	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void put_bomb();

public:

	Bomberman(GameMap & game_map);
	~Bomberman() {};

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
	bool IsAlive();
};

/* ======================================================================
* Bomb
* =================================================================== */

class Bomb : public Sprite
{
	friend class Bomberman;
private:
	long long _count_down;
	long long _explosion_animation_counter;
	int _power;
	bool _removable;
	GameMap & _map;

	void draw_center_flame(int const & animation_state);
	void draw_vertical_flame(int const & animation_state);
	void draw_horizontal_flame(int const & animation_state);
public:
	Bomb(Vector2 const & position, GameMap & game_map);
	~Bomb();

	void detonate();
	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};