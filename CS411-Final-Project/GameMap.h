#pragma once
#include "Vector2.h"

class GameMap
{
private:
	bool loaded;
	char ** grid;
	Vector2 _starting_pos;
public:
	GameMap(int const & level);
	~GameMap();

	bool is_loaded();
};