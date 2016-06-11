#include "Bomberman.h"
#include <cmath>
using namespace std;

/* ======================================================================
 * Bomberman
 * =================================================================== */

Bomberman::Bomberman(GameMap & game_map) : Sprite("Bomberman"), _map(game_map)
{
	_numBomb = 1;
	_isAlive = true;
	_move_time = 0;
	_moving_dir = 2;
}

void Bomberman::Update(long long const & totalTime, long long const & elapsedTime)
{
	Sprite::Update(totalTime, elapsedTime);
	for (list<Bomb*>::iterator it = _bombs.begin(); !_bombs.empty() && it != _bombs.end(); ++it)
	{
		(*it)->Update(totalTime, elapsedTime);
		// reset number if the bomb has just exploded
		if ((*it)->_explosion_animation_counter == elapsedTime)
			++_numBomb;
	}


	while (!_bombs.empty() && _bombs.front()->_removable)
	{
		delete _bombs.front();
		_bombs.pop_front();
	}

	if (_isAlive)
	{
		UpdateMovement(totalTime, elapsedTime);

		if (_map.Get_Square(_rect[0]) == '4' ||
			_map.Get_Square(_rect[0]) == '5')
			_isAlive = false;

		if (KeyboardManager::is_key_pressed(' '))
			put_bomb();
	}
}

void Bomberman::UpdateMovement(long long const & totalTime, long long const & elapsedTime)
{
	if (!_is_moving)
	{
		if (KeyboardManager::is_special_pressed(GLUT_KEY_DOWN))
		{
			_moving_dir = 2;
			if (!_map.can_move({ _rect[0].x, _rect[0].y - 32 }))
				return;
			_is_moving = true;
		}
		else if (KeyboardManager::is_special_pressed(GLUT_KEY_UP))
		{
			_moving_dir = 8;
			if (!_map.can_move({ _rect[0].x, _rect[0].y + 32 }))
				return;
			_is_moving = true;
		}
		else if (KeyboardManager::is_special_pressed(GLUT_KEY_LEFT))
		{
			_moving_dir = 4;
			if (!_map.can_move({ _rect[0].x - 32 , _rect[0].y }))
				return;
			_is_moving = true;
		}
		else if (KeyboardManager::is_special_pressed(GLUT_KEY_RIGHT))
		{
			_moving_dir = 6;
			if (!_map.can_move({ _rect[0].x + 32, _rect[0].y }))
				return;
			_is_moving = true;
		}
	}
	else
	{
		_move_time += elapsedTime;

		double dx = 0, dy = 0, d = 32.0;
		switch (_moving_dir)
		{
		case 2:
			dy = -d * elapsedTime / MOVE_TIME;
			break;
		case 4:
			dx = -d * elapsedTime / MOVE_TIME;
			break;
		case 6:
			dx = d * elapsedTime / MOVE_TIME;
			break;
		case 8:
			dy = d * elapsedTime / MOVE_TIME;
			break;
		default:
			break;
		}

		double x = _rect[0].x + dx;
		double y = _rect[0].y + dy;
		if (_move_time > MOVE_TIME)
		{
			if (dx > 0)
				x = round(x - d * (_move_time - MOVE_TIME) / MOVE_TIME);
			else if (dx < 0)
				x = round(x + d * (_move_time - MOVE_TIME) / MOVE_TIME);

			if (dy > 0)
				y = round(y - d * (_move_time - MOVE_TIME) / MOVE_TIME);
			else if (dy < 0)
				y = round(y + d * (_move_time - MOVE_TIME) / MOVE_TIME);
		}
		
		set_position({ x, y });

		if (_move_time >= MOVE_TIME)
		{
			_move_time = 0;
			_is_moving = false;
		}
	}
}

void Bomberman::Draw()
{
	for (list<Bomb*>::iterator it = _bombs.begin(); !_bombs.empty() && it != _bombs.end(); ++it)
		(*it)->Draw();
	
	double dir_idx = (10 - _moving_dir) / 2 - 1;
	double frame_idx = (int)(((double)_move_time / MOVE_TIME) * 4);

	TextureManager::BindTexture(_name);
	glBegin(GL_QUADS);
	glTexCoord2d(frame_idx / 4, dir_idx / 4); glVertex2d(_tmp_rect[0].x, _tmp_rect[0].y); // top left
	glTexCoord2d((frame_idx + 1) / 4, dir_idx / 4); glVertex2d(_tmp_rect[0].x + 32, _tmp_rect[0].y); // top right
	glTexCoord2d((frame_idx + 1) / 4, (dir_idx + 1) / 4); glVertex2d(_tmp_rect[0].x + 32, _tmp_rect[0].y + 32); // bottom right
	glTexCoord2d(frame_idx / 4, (dir_idx + 1) / 4); glVertex2d(_tmp_rect[0].x, _tmp_rect[0].y + 32); // bottom left
	glEnd();
}

void Bomberman::put_bomb()
{
	if (_numBomb > 0)
	{
		--_numBomb;
		_bombs.push_back(new Bomb(_map.Position_Of_Nearest_Square(_rect[0]), _map));
	}
}

bool Bomberman::IsAlive()
{
	return _isAlive;
}


/* ======================================================================
 * Bomb
 * =================================================================== */

Bomb::Bomb(Vector2 const & position, GameMap & game_map) : Sprite("Bomb"), _map(game_map)
{
	_count_down = 3000;
	_power = 3;
	_removable = false;
	_explosion_animation_counter = 0;
	set_position(position);
	_map.Change_Square(position, '3');
}

Bomb::~Bomb()
{
	for (int direction = 0; direction < 2; ++direction)
	{
		for (int sign = -1; sign < 2; sign += 2)
		{
			for (int i = 1; i < _power; ++i)
			{
				Vector2 pos = { _rect[0].x + direction * sign * i * 32, _rect[0].y + (1 - direction) * sign * i * 32 };
				if (_map.InBound(pos))
				{
					char tmp = _map.Get_Square(pos);
					if (tmp == '4')
						_map.Change_Square(pos, '0');
				}
			}
		}
	}

	_map.Change_Square(_rect[0], '0');
}

void Bomb::Update(long long const & totalTime, long long const & elapsedTime)
{
	Sprite::Update(totalTime, elapsedTime);

	if (_count_down > 0 && _map.Get_Square(_rect[0]) == '4')
		detonate();

	if (_count_down > 0)
	{
		_count_down -= elapsedTime;

		double scale = 1 + 0.07 * cos(totalTime * PI / 300);
		Matrix matrix;
		matrix.Translate(-_rect[0].x - 16, -_rect[0].y - 16);
		matrix.Scale(scale, scale);
		matrix.Translate(_rect[0].x + 16, _rect[0].y + 16);
		ApplyMatrix(matrix);
	}
	else
	{
		if (_explosion_animation_counter == 0)
		{
			_map.Change_Square(_rect[0], '4');
			// calculate explosion area
			for (int direction = 0; direction < 2; ++direction)
			{
				for (int sign = -1; sign < 2; sign += 2)
				{
					for (int i = 1; i < _power; ++i)
					{
						Vector2 pos = { _rect[0].x + direction * sign * i * 32, _rect[0].y + (1 - direction) * sign * i * 32 };
						char tmp = _map.Get_Square(pos);
						if (tmp == '1')
						{
							_map.Change_Square(pos, '4');
							Score += 10;
							break;
						}

						if (tmp != '0' && tmp != '3' && tmp != '5')
							break;
						else if (tmp == '3')
						{
							_map.Change_Square(pos, '4');
							break;
						}
						else
							_map.Change_Square(pos, '4');
					}
				}
			}
		}
		_explosion_animation_counter += elapsedTime;
		if (_explosion_animation_counter > 350)
			_removable = true;
	}
}

void Bomb::detonate()
{
	_count_down = 0;
}

void Bomb::Draw()
{
	if (_count_down > 0)
		Sprite::Draw();
	else
	{
		TextureManager::BindTexture("Explosion");
		int animation_state = _explosion_animation_counter / 100;

		glBegin(GL_QUADS);
		draw_center_flame(animation_state);
		draw_vertical_flame(animation_state);
		draw_horizontal_flame(animation_state);
		glEnd();
	}
}

void Bomb::draw_center_flame(int const & animation_state)
{
	// explosion center
	glTexCoord2d(0 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[0].x, _rect[0].y); // top left
	glTexCoord2d(1 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[1].x, _rect[1].y); // top right
	glTexCoord2d(1 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[2].x, _rect[2].y); // bottom right
	glTexCoord2d(0 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[3].x, _rect[3].y); // bottom left

}

void Bomb::draw_vertical_flame(int const & animation_state)
{
	// vertical flame
	for (int sign = -1; sign < 2; sign += 2)
	{
		for (int offset = 1; offset < _power - 1; ++offset)
		{
			double tmp = _rect[0].y + sign * 32 * offset;
			if (!_map.InBound({ _rect[0].x, tmp }) || _map.Get_Square({ _rect[0].x, tmp }) != '4')
				break;

			glTexCoord2d(1 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[0].x, _rect[0].y + sign * 32 * offset); // top left
			glTexCoord2d(2 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[1].x, _rect[1].y + sign * 32 * offset); // top right
			glTexCoord2d(2 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[2].x, _rect[2].y + sign * 32 * offset); // bottom right
			glTexCoord2d(1 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[3].x, _rect[3].y + sign * 32 * offset); // bottom left
		}
	}

	for (int sign = -1, offset = _power - 1; sign < 2; sign += 2)
	{
		double tmp = _rect[0].y + sign * 32 * offset;
		if (!_map.InBound({ _rect[0].x, tmp }) || _map.Get_Square({ _rect[0].x, tmp }) != '4')
			continue;

		int t1 = (sign == 1) ? 3 : 4;
		glTexCoord2d(t1 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[0].x, _rect[0].y + sign * 32 * offset); // top left
		glTexCoord2d((t1 + 1) / 7.0f, animation_state / 4.0f); glVertex2d(_rect[1].x, _rect[1].y + sign * 32 * offset); // top right
		glTexCoord2d((t1 + 1) / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[2].x, _rect[2].y + sign * 32 * offset); // bottom right
		glTexCoord2d(t1 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[3].x, _rect[3].y + sign * 32 * offset); // bottom left
	}
}

void Bomb::draw_horizontal_flame(int const & animation_state)
{
	// horizontal flame
	for (int sign = -1; sign < 2; sign += 2)
	{
		for (int offset = 1; offset < _power - 1; ++offset)
		{
			double tmp = _rect[0].x + sign * 32 * offset;
			if (!_map.InBound({ tmp, _rect[0].y }) || _map.Get_Square({ tmp, _rect[0].y }) != '4')
				break;

			glTexCoord2d(2 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[0].x + sign * 32 * offset, _rect[0].y); // top left
			glTexCoord2d(3 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[1].x + sign * 32 * offset, _rect[1].y); // top right
			glTexCoord2d(3 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[2].x + sign * 32 * offset, _rect[2].y); // bottom right
			glTexCoord2d(2 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[3].x + sign * 32 * offset, _rect[3].y); // bottom left
		}
	}

	for (int sign = -1, offset = _power - 1; sign < 2; sign += 2)
	{
		double tmp = _rect[0].x + sign * 32 * offset;
		if (!_map.InBound({ tmp, _rect[0].y }) || _map.Get_Square({ tmp, _rect[0].y }) != '4')
			continue;

		int t1 = (sign == 1) ? 5 : 6;
		glTexCoord2d(t1 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[0].x + sign * 32 * offset, _rect[0].y); // top left
		glTexCoord2d((t1 + 1) / 7.0f, animation_state / 4.0f); glVertex2d(_rect[1].x + sign * 32 * offset, _rect[1].y); // top right
		glTexCoord2d((t1 + 1) / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[2].x + sign * 32 * offset, _rect[2].y); // bottom right
		glTexCoord2d(t1 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[3].x + sign * 32 * offset, _rect[3].y); // bottom left
	}
}