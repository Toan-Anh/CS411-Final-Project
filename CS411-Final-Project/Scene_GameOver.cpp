#include "Scene_GameOver.h"
#include <cmath>
using namespace std;

Scene_GameOver::Scene_GameOver()
{
	Score = 0;
	_sprites.push_back(new Sprite("Game Over"));
	_sprites[0]->set_position({ 0, 20 });

	yes.push_back(Sprite("Yes Normal"));
	yes.push_back(Sprite("Yes Highlight"));
	yes.push_back(Sprite("Yes Selected"));
	yes.push_back(Sprite("Yes Locked"));

	no.push_back(Sprite("No Normal"));
	no.push_back(Sprite("No Highlight"));
	no.push_back(Sprite("No Selected"));
	no.push_back(Sprite("No Locked"));

	for (int i = 0; i < 4; ++i)
	{
		yes[i].set_position({150, 150});
		no[i].set_position({418, 150});
	}

	selected = 0;
	confirmed = -1;
	wait = 300;
}

Scene_GameOver::~Scene_GameOver()
{
}

void Scene_GameOver::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);

	if (confirmed > -1)
	{
		wait -= elapsedTime;
		if (wait <= 0)
		{
			switch (confirmed)
			{
			case 0:
				SceneManager::ReturnScene();
				break;
			case 1: // Exit
				GameManager::ExitGame();
				break;
			default:
				break;
			}
		}

		return;
	}

	if (KeyboardManager::is_key_pressed('\r') ||
		KeyboardManager::is_key_pressed('\n'))
		SceneManager::ReturnScene();

	if (KeyboardManager::is_special_pressed(GLUT_KEY_RIGHT))
		selected = (selected + 1) % 2;
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_LEFT))
		selected = abs((selected - 1) % 2);
	else if (KeyboardManager::is_key_pressed(' '))
		confirmed = selected;
}

void Scene_GameOver::Draw()
{
	SceneManager::DrawSnapShot();
	Scene::Draw();

	for (int i = 0; i < 2; ++i)
	{
		int t;
		if (i == confirmed)
			t = 2;
		else if (i == selected)
			t = 1;
		else
			t = 0;

		Sprite& tmp = i == 0 ? yes[t] : no[t];
		tmp.Draw();
	}
}