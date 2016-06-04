#pragma once
#include "GameManager.h"
#include "SceneManager.h"

class Scene_GameOver : public Scene
{
private:
	vector<Sprite> yes;
	vector<Sprite> no;
	int selected;
	int confirmed;

	long long wait;
public:
	Scene_GameOver();
	~Scene_GameOver();

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};