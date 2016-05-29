#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "KeyboardManager.h"
#include <vector>
using namespace std;

class Scene
{
protected:
	vector<Sprite*> _sprites;
public:
	Scene();
	virtual ~Scene();

	virtual void Update(long long const & totalTime, long long const & elapsedTime);
	virtual void Draw();
};