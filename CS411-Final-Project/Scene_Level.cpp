#include "Scene_Level.h"

Scene_Level::Scene_Level(int const & level)
{
	_sprites.push_back(new Boomberman("Bomberman_down"));
	_sprites[0]->set_position({ 0, 0 });
}

Scene_Level::~Scene_Level()
{

}

void Scene_Level::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);
	
	if (KeyboardManager::is_special_pressed(GLUT_KEY_DOWN))
		_sprites[0]->move_down();
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_UP))
		_sprites[0]->move_up();
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_LEFT))
		_sprites[0]->move_left();
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_RIGHT))
		_sprites[0]->move_right();


	if (KeyboardManager::is_key_pressed('\r') ||
		KeyboardManager::is_key_pressed('\n'))
		SceneManager::AddScene(new Scene_Menu());
}

void Scene_Level::Draw()
{
	Scene::Draw();
}