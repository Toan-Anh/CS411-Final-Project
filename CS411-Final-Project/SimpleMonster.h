#pragma once
#include "Monster.h"

class SimpleMonster : public Monster
{
private:
	const long long MONSTER_MOVE_TIME = 500;
	vector<Vector2> _move_path;
	int _current_pos_index;
	bool _turn_around;
	int _current_tex_idx;
	long long _move_timer;

	void move_forward();
	void move_backward();
public:
	SimpleMonster(string const & name, GameMap & game_map, Vector2 const & start, vector<pair<int, int>> const & command);
	~SimpleMonster() {};

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};