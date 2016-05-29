#pragma once
#include "Sprite.h"

class Bomb : public Sprite
{
private:
	int _count_down;
public:
	Bomb();
	~Bomb();

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};