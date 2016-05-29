#include "Scene_Menu.h"

Scene_Menu::Scene_Menu()
{
	_sprites.push_back(new Sprite("Paused Menu"));
	button.push_back(Sprite("Button Normal"));
	button.push_back(Sprite("Button Highlight"));
	button.push_back(Sprite("Button Selected"));
	button.push_back(Sprite("Button Locked"));

	_sprites[0]->set_position({ 157, 20 });
}

Scene_Menu::~Scene_Menu()
{
}

void Scene_Menu::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);

	if (KeyboardManager::is_key_pressed('\r') ||
		KeyboardManager::is_key_pressed('\n'))
		SceneManager::ReturnScene();
}

void Scene_Menu::Draw()
{
	Scene::Draw();
}