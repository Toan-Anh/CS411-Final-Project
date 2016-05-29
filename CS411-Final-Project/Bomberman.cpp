#include "Bomberman.h"

Bomberman::Bomberman(const string& name) : Sprite(name)
{
	_numBoom = 1;
	_isAlive = true;
}

void Bomberman::Update()
{
	if (KeyboardManager::is_special_pressed(GLUT_KEY_DOWN))
		move_down();
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_UP))
		move_up();
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_LEFT))
		move_left();
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_RIGHT))
		move_right();
}

void Bomberman::Draw()
{
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

void Bomberman::put_boom()
{
}


void Bomberman::move_up()
{
	_rect[0].y += MOVE_STEP;
	set_position(_rect[0]);
}