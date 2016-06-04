#pragma once
#include "Sprite.h"
#include "KeyboardManager.h"
#include "SceneManager.h"
#include "GameMap.h"
#include "Global.h"

class Monster : public Sprite
{
protected:
	int _health;
	bool _isAlive;
	GameMap& _map;

	void move_left();
	void move_right();
	void move_up();
	void move_down();

public:
	Monster(string const & tex_name, GameMap & game_map);
	~Monster() {};

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
	bool IsAlive();
};