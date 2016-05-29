#include "SceneManager.h"

stack<Scene*> SceneManager::_scenes;
unsigned char SceneManager::buffer[640 * 480 * 4];

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

void SceneManager::SnapShot()
{
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, 640, 480, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
}

void SceneManager::DrawSnapShot()
{
	glRasterPos2i(0, 0);
	glDrawPixels(640, 480, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
}