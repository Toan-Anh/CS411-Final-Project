#include "Scene_Start.h"
#include <cmath>
#include <iostream>
using namespace std;

Scene_Start::Scene_Start()
{
	_sprites.push_back(new Sprite("Title Screen"));
	_sprites.push_back(new Sprite("Title"));
	_sprites.push_back(new Sprite("Enter"));
	
	_sprites[1]->set_position({ 60, 240 });
	_sprites[2]->set_position({ 170, 80 });
	


}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);

	if (KeyboardManager::is_key_pressed('\r') ||
		KeyboardManager::is_key_pressed('\n'))
		SceneManager::AddScene(new Scene_Level(1));
	
	Vector2 tmp = _sprites[2]->get_position();
	_sprites[2]->set_position({tmp.x, 80 + 5 * cos(0.009 * totalTime)});
}

void Scene_Start::Draw()
{
	Scene::Draw();
}