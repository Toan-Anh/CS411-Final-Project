#include "Monster.h"

Monster::Monster(string const & tex_name, GameMap & game_map) : Sprite(tex_name), _map(game_map)
{
	_isAlive = true;
}

void Monster::Update(long long const & totalTime, long long const & elapsedTime)
{
	Sprite::Update(totalTime, elapsedTime);
}

void Monster::Draw()
{
	Sprite::Draw();
}

void Monster::move_left()
{
}

void Monster::move_right()
{
}

void Monster::move_down()
{
}

void Monster::move_up()
{
}

bool Monster::IsAlive()
{
	return _isAlive;
}