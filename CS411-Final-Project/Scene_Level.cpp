#include "Scene_Level.h"

Scene_Level::Scene_Level(int const & level) : _map(level, { 160, 0 })
{
	_sprites.push_back(new Bomberman(_map));	
	if (_map.is_loaded())
		_sprites[0]->set_position(_map.bomberman_starting_pos());

	for (int i = 0; i < 9; ++i)
		_sprites.push_back(new Sprite("Num_" + to_string(i)));
}

Scene_Level::~Scene_Level()
{

}

void Scene_Level::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);

	if (KeyboardManager::is_key_pressed('\r') ||
		KeyboardManager::is_key_pressed('\n'))
	{
		SceneManager::SnapShot();
		SceneManager::AddScene(new Scene_Menu());
	}
}



void Scene_Level::Draw()
{
	if (_map.is_loaded())
		_map.Draw();
	Scene::Draw();
}