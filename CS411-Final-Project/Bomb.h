#pragma once
#include "Sprite.h"

class Bomb : public Sprite
{
private:
public:
	Bomb();
	~Bomb();

	void Update();
	void Draw();
};