#pragma once
#include "SceneManager.h"
#include "Scene_LevelSelection.h"
using namespace std;

class Scene_Start : public Scene
{
private:
public:
	Scene_Start();
	~Scene_Start();

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};