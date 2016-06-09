#include "Scene_Congratulations.h"
#include <fstream>
using namespace std;

Scene_Congratulations::Scene_Congratulations()
{
	_sprites.push_back(new Sprite("Congratulations"));
	ofstream fout;
	fout.open("GameData");
	if (!fout.is_open())
		return;
	for (unordered_map<int, int>::const_iterator it = BestScores.cbegin(); it != BestScores.cend(); ++it)
		fout << it->first << " " << it->second << endl;
	fout.close();
}

Scene_Congratulations::~Scene_Congratulations()
{
}

void Scene_Congratulations::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);

	if (KeyboardManager::is_key_pressed('\r') ||
		KeyboardManager::is_key_pressed('\n'))
	{
		SceneManager::ReturnScene();
		SceneManager::ChangeScene(new Scene_Start());
	}
}

void Scene_Congratulations::Draw()
{
	Scene::Draw();
}