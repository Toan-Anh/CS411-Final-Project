#include "Bomberman.h"

Boomberman::Boomberman(const string& name) : Sprite(name)
{
	_numBoom = 1;
	_isAlive = true;
}

void Boomberman::move_left()
{
	_rect[0].x -= MOVE_STEP;
	set_position(_rect[0]);
}

void Boomberman::move_right()
{
	_rect[0].x += MOVE_STEP;
	set_position(_rect[0]);
}

void Boomberman::move_down()
{
	_rect[0].y -= MOVE_STEP;
	set_position(_rect[0]);
}

void Boomberman::put_boom()
{
}


void Boomberman::move_up()
{
	_rect[0].y += MOVE_STEP;
	set_position(_rect[0]);
}


