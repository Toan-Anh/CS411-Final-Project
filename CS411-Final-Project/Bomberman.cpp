#include "Bomberman.h"

/* ======================================================================
 * Bomberman
 * =================================================================== */

Bomberman::Bomberman(const string& name) : Sprite(name)
{
	_numBomb = 2;
	_isAlive = true;
}

void Bomberman::Update(long long const & totalTime, long long const & elapsedTime)
{
	Sprite::Update(totalTime, elapsedTime);
	for (list<Bomb>::iterator it = _bombs.begin(); !_bombs.empty() && it != _bombs.end(); ++it)
	{
		it->Update(totalTime, elapsedTime);
		// reset number if the bomb has just exploded
		if (it->_explostion_animation_counter == elapsedTime)
			++_numBomb;
	}


	while (!_bombs.empty() && _bombs.front()._removable)
		_bombs.pop_front();


	if (KeyboardManager::is_special_pressed(GLUT_KEY_DOWN))
		move_down();
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_UP))
		move_up();
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_LEFT))
		move_left();
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_RIGHT))
		move_right();

	if (KeyboardManager::is_key_pressed(' '))
		put_bomb();
}

void Bomberman::Draw()
{
	for (list<Bomb>::iterator it = _bombs.begin(); !_bombs.empty() && it != _bombs.end(); ++it)
		it->Draw();
	Sprite::Draw();
}

void Bomberman::move_left()
{
	_rect[0].x -= MOVE_STEP;
	set_position(_rect[0]);
}

void Bomberman::move_right()
{
	_rect[0].x += MOVE_STEP;
	set_position(_rect[0]);
}

void Bomberman::move_down()
{
	_rect[0].y -= MOVE_STEP;
	set_position(_rect[0]);
}

void Bomberman::put_bomb()
{
	if (_numBomb > 0)
	{
		--_numBomb;
		_bombs.push_back(Bomb(_rect[0]));
	}
}

void Bomberman::move_up()
{
	_rect[0].y += MOVE_STEP;
	set_position(_rect[0]);
}


/* ======================================================================
 * Bomb
 * =================================================================== */

Bomb::Bomb(Vector2 const & position) : Sprite("Bomb")
{
	_count_down = 3000;
	_power = 4;
	_removable = false;
	_explostion_animation_counter = 0;
	set_position(position);
}

Bomb::~Bomb()
{
}

void Bomb::Update(long long const & totalTime, long long const & elapsedTime)
{
	Sprite::Update(totalTime, elapsedTime);

	if (_count_down > 0)
		_count_down -= elapsedTime;
	else
	{
		_explostion_animation_counter += elapsedTime;
		if (_explostion_animation_counter > 350)
			_removable = true;
	}
}

void Bomb::Draw()
{
	if (_count_down > 0)
		Sprite::Draw();
	else
	{
		TextureManager::BindTexture("Explosion");
		int animation_state = _explostion_animation_counter / 100;

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
	int offset;
	for (offset = 1; offset < _power - 1; ++offset)
	{
		for (int sign = -1; sign < 2; sign += 2)
		{
			for (int i = 0; i < 4; ++i)
			{
				glTexCoord2d(1 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[0].x, _rect[0].y + sign * 32 * offset); // top left
				glTexCoord2d(2 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[1].x, _rect[1].y + sign * 32 * offset); // top right
				glTexCoord2d(2 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[2].x, _rect[2].y + sign * 32 * offset); // bottom right
				glTexCoord2d(1 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[3].x, _rect[3].y + sign * 32 * offset); // bottom left
			}
		}
	}

	for (int sign = -1; sign < 2; sign += 2)
	{
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
	int offset;
	for (offset = 1; offset < _power - 1; ++offset)
	{
		for (int sign = -1; sign < 2; sign += 2)
		{
			for (int i = 0; i < 4; ++i)
			{
				glTexCoord2d(2 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[0].x + sign * 32 * offset, _rect[0].y); // top left
				glTexCoord2d(3 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[1].x + sign * 32 * offset, _rect[1].y); // top right
				glTexCoord2d(3 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[2].x + sign * 32 * offset, _rect[2].y); // bottom right
				glTexCoord2d(2 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[3].x + sign * 32 * offset, _rect[3].y); // bottom left
			}
		}
	}

	for (int sign = -1; sign < 2; sign += 2)
	{
		int t1 = (sign == 1) ? 5 : 6;
		glTexCoord2d(t1 / 7.0f, animation_state / 4.0f); glVertex2d(_rect[0].x + sign * 32 * offset, _rect[0].y); // top left
		glTexCoord2d((t1 + 1) / 7.0f, animation_state / 4.0f); glVertex2d(_rect[1].x + sign * 32 * offset, _rect[1].y); // top right
		glTexCoord2d((t1 + 1) / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[2].x + sign * 32 * offset, _rect[2].y); // bottom right
		glTexCoord2d(t1 / 7.0f, (animation_state + 1) / 4.0f); glVertex2d(_rect[3].x + sign * 32 * offset, _rect[3].y); // bottom left
	}
}