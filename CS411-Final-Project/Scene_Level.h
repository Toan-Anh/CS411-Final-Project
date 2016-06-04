#pragma once
#include "SceneManager.h"
#include "Scene_Menu.h"
#include "Bomberman.h"
#include "GameMap.h"
#include "Monster.h"
#include "SimpleMonster.h"
using namespace std;

class Scene_Level : public Scene
{
private:
	GameMap _map;
	vector<Monster*> _monsters;
public:
	Scene_Level(int const & level);
	~Scene_Level();

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};