#include "SimpleMonster.h"
#include <cmath>
using namespace std;

SimpleMonster::SimpleMonster(string const & tex_name, GameMap & game_map, Vector2 const & start, vector<pair<int, int>> const & command) : Monster(tex_name, game_map), _current_pos_index(0)
{
	_health = 1;
	_dead_anim_timer = 500;

	_current_pos_index = 0;
	_turn_around = false;
	_move_timer = 0;
	_current_tex_idx = 0;
	set_position(start);
	_map.Change_Square(start, '5');

	Vector2 cur = start;
	_move_path.push_back(cur);
	for (int i = 0; i < command.size(); ++i)
	{
		for (int j = 0; j < command[i].second; ++j)
		{
			Vector2 tmp = { 0, 0 };
			switch (command[i].first)
			{
			case 2:
				tmp = { 0, -32 };
				break;
			case 4:
				tmp = { -32, 0 };
				break;
			case 6:
				tmp = { 32, 0 };
				break;
			case 8:
				tmp = { 0, 32 };
				break;
			default:
				break;
			}

			cur = cur + tmp;
			_move_path.push_back(cur);
		}
	}
}

void SimpleMonster::Update(long long const & totalTime, long long const & elapsedTime)
{
	Monster::Update(totalTime, elapsedTime);

	_current_tex_idx = 1 + cos(totalTime * 0.027);

	if (_map.Get_Square(_rect[0]) == '4')
		--_health;

	if (_health > 0)
	{
		if (_move_timer > MONSTER_MOVE_TIME)
		{
			if (!_turn_around)
				move_forward();
			if (_turn_around)
				move_backward();

			_move_timer = 0;
		}
		else
			_move_timer += elapsedTime;
	}
	else
	{
		if (_dead_anim_timer <= 0)
		{
		}
		else
			_dead_anim_timer -= elapsedTime;
	}
}

void SimpleMonster::Draw()
{
	//Monster::Draw();
	TextureManager::BindTexture(_name);
	glBegin(GL_QUADS);
	glTexCoord2d(_current_tex_idx / 3.0f, 0.0f); glVertex2d(_tmp_rect[0].x, _tmp_rect[0].y); // top left
	glTexCoord2d((_current_tex_idx + 1) / 3.0f, 0.0f); glVertex2d(_tmp_rect[0].x + 32, _tmp_rect[0].y); // top right
	glTexCoord2d((_current_tex_idx + 1) / 3.0f, 1.0f); glVertex2d(_tmp_rect[0].x + 32, _tmp_rect[0].y + 32); // bottom right
	glTexCoord2d(_current_tex_idx / 3.0f, 1.0f); glVertex2d(_tmp_rect[0].x, _tmp_rect[0].y + 32); // bottom left
	glEnd();
}

void SimpleMonster::move_forward()
{
	if (_current_pos_index < _move_path.size() - 1)
	{
		Vector2 tmp = _move_path[_current_pos_index + 1];
		if (_map.can_move(tmp))
		{
			if (_map.Get_Square(_rect[0]) != '4' && _map.Get_Square(tmp) != '4')
			{
				_map.Change_Square(_rect[0], '0');
				_map.Change_Square(tmp, '5');
			}
			else
				--_health;

			set_position(tmp);
			++_current_pos_index;
		}
		else
			_turn_around = true;
	}
	else
		_turn_around = true;
}

void SimpleMonster::move_backward()
{
	if (_current_pos_index > 0)
	{
		Vector2 tmp = _move_path[_current_pos_index - 1];
		if (_map.can_move(tmp))
		{
			if (_map.Get_Square(_rect[0]) != '4' && _map.Get_Square(tmp) != '4')
			{
				_map.Change_Square(_rect[0], '0');
				_map.Change_Square(tmp, '5');
			}
			else
				--_health;

			set_position(tmp);
			--_current_pos_index;
		}
		else
			_turn_around = false;
	}
	else
		_turn_around = false;
}