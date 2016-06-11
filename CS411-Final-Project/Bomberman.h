#pragma once
#include "Sprite.h"
#include "KeyboardManager.h"
#include "SceneManager.h"
#include "Scene_GameOver.h"
#include "GameMap.h"

static const long long MOVE_TIME = 250;

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
	long long _move_time;
	int _moving_dir;
	bool _is_moving;

	void put_bomb();
	void UpdateMovement(long long const & totalTime, long long const & elapsedTime);

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