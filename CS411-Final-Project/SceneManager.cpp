#include "SceneManager.h"

stack<Scene*> SceneManager::_scenes;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

Scene* SceneManager::CurrentScene()
{
	if (!_scenes.empty())
		return _scenes.top();
	return nullptr;
}

void SceneManager::AddScene(Scene * scene)
{
	_scenes.push(scene);
}

void SceneManager::ReturnScene()
{
	if (!_scenes.empty())
		_scenes.pop();
}

void SceneManager::ChangeScene(Scene * scene)
{
	delete _scenes.top();
	_scenes.pop();
	_scenes.push(scene);
}

void SceneManager::CleanUp()
{
	while (!_scenes.empty())
	{
		delete _scenes.top();
		_scenes.pop();
	}
}