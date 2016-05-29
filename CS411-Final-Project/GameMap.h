#pragma once
#include "Vector2.h"
#include "TextureManager.h"

class GameMap
{
private:
	bool _loaded;

	int _width, _height;
	char ** _grid;

	Vector2 _starting_pos;
	Vector2 _bomberman;
public:
	GameMap(int const & level, Vector2 const & start);
	~GameMap();

	bool is_loaded();
	Vector2 bomberman_starting_pos();
	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};