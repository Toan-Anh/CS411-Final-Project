#include "Scene_Congratulations.h"

Scene_Congratulations::Scene_Congratulations()
{
	_sprites.push_back(new Sprite("Congratulations"));
}

Scene_Congratulations::~Scene_Congratulations()
{
}

void Scene_Congratulations::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);

	if (KeyboardManager::is_key_pressed('\r') ||
		KeyboardManager::is_key_pressed('\n'))
		SceneManager::ReturnScene();
}

void Scene_Congratulations::Draw()
{
	Scene::Draw();
}