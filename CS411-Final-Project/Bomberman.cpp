#include "Bomberman.h"

/* ======================================================================
 * Bomberman
 * =================================================================== */

Bomberman::Bomberman(GameMap & game_map) : Sprite("Bomberman_down"), _map(game_map)
{
	_numBomb = 2;
	_isAlive = true;
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
		if (KeyboardManager::is_special_pressed(GLUT_KEY_DOWN))
			move_down();
		else if (KeyboardManager::is_special_pressed(GLUT_KEY_UP))
			move_up();
		else if (KeyboardManager::is_special_pressed(GLUT_KEY_LEFT))
			move_left();
		else if (KeyboardManager::is_special_pressed(GLUT_KEY_RIGHT))
			move_right();

		if (_map.Get_Square(_rect[0]) == '4')
			_isAlive = false;

		if (KeyboardManager::is_key_pressed(' '))
			put_bomb();
	}
}

void Bomberman::Draw()
{
	for (list<Bomb*>::iterator it = _bombs.begin(); !_bombs.empty() && it != _bombs.end(); ++it)
		(*it)->Draw();
	Sprite::Draw();
}

void Bomberman::move_left()
{
	Vector2 pos = { _rect[0].x - MOVE_STEP, _rect[0].y };
	if (_map.can_move(pos))
		set_position(pos);
}

void Bomberman::move_right()
{
	Vector2 pos = { _rect[0].x + MOVE_STEP, _rect[0].y };
	if (_map.can_move(pos))
		set_position(pos);
}

void Bomberman::move_down()
{
	Vector2 pos = { _rect[0].x, _rect[0].y - MOVE_STEP };
	if (_map.can_move(pos))
		set_position(pos);
}

void Bomberman::move_up()
{
	Vector2 pos = { _rect[0].x, _rect[0].y + MOVE_STEP };
	if (_map.can_move(pos))
		set_position(pos);
}

void Bomberman::put_bomb()
{
	if (_numBomb > 0)
	{
		--_numBomb;
		_bombs.push_back(new Bomb(_rect[0], _map));
	}
}


/* ======================================================================
 * Bomb
 * =================================================================== */

Bomb::Bomb(Vector2 const & position, GameMap & game_map) : Sprite("Bomb"), _map(game_map)
{
	_count_down = 3000;
	_power = 5;
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
		_count_down -= elapsedTime;
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
							break;
						}

						if (tmp != '0' && tmp != '3')
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