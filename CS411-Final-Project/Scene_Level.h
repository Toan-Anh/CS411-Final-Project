#pragma once
#include "SceneManager.h"
using namespace std;

class Scene_Level : public Scene
{
private:
public:
	Scene_Level(int const & level);
	~Scene_Level();

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};