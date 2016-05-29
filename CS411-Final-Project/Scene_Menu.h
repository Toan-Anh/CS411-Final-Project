#pragma once
#include "SceneManager.h"
#include "Scene_Level.h"
using namespace std;

class Scene_Menu : public Scene
{
private:
	vector<Sprite> button;
public:
	Scene_Menu();
	~Scene_Menu();

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};