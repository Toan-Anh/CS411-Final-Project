#include "Scene_Level.h"

Scene_Level::Scene_Level(int const & level)
{

}

Scene_Level::~Scene_Level()
{

}

void Scene_Level::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);

	if (KeyboardManager::is_key_pressed('\r') ||
		KeyboardManager::is_key_pressed('\n'))
		SceneManager::AddScene(new Scene_Menu());
}

void Scene_Level::Draw()
{
	Scene::Draw();
}