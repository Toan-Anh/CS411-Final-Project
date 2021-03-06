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
	vector<int> _monster_info;
public:
	GameMap(int const & level, Vector2 const & start);
	~GameMap();

	bool is_loaded();
	Vector2 bomberman_starting_pos();
	bool can_move(Vector2 const & pos);
	void Change_Square(int const & row, int const & column, char const & value);
	char Get_Square(int const & row, int const & column);
	void Change_Square(Vector2 const & pos, char const & value);
	char Get_Square(Vector2 const & pos);
	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
	bool InBound(Vector2 const & pos);
	Vector2 Get_Position_From_Grid(int const & r, int const & c);
	Vector2 Position_Of_Nearest_Square(Vector2 const & pos);
	vector<int> get_monster_info();
};