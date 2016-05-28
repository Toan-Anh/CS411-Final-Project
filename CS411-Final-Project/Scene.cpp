#include "Scene.h"
#include "Matrix.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (vector<Sprite*>::iterator it = _sprites.begin(); it != _sprites.end(); ++it)
		delete (*it);
}

void Scene::Update(long long const & totalTime, long long const & elapsedTime)
{
	for (vector<Sprite*>::iterator it = _sprites.begin(); it != _sprites.end(); ++it)
		(*it)->Update();
}

void Scene::Draw()
{
	for (vector<Sprite*>::iterator it = _sprites.begin(); it != _sprites.end(); ++it)
		(*it)->Draw();
}