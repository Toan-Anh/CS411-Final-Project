#include "Bomb.h"

Bomb::Bomb() : Sprite("Bomb")
{
	_count_down = 3000;
}

Bomb::~Bomb()
{

}

void Bomb::Update(long long const & totalTime, long long const & elapsedTime)
{
	Sprite::Update(totalTime, elapsedTime);
}

void Bomb::Draw()
{
	Sprite::Draw();
}