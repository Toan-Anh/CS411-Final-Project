#include "Scene_Menu.h"
#include <cmath>
using namespace std;

Scene_Menu::Scene_Menu()
{
	_sprites.push_back(new Sprite("Paused Menu"));
	_sprites[0]->set_position({ 157, 20 });

	button_state.push_back(Sprite("Button Normal"));
	button_state.push_back(Sprite("Button Highlight"));
	button_state.push_back(Sprite("Button Selected"));
	button_state.push_back(Sprite("Button Locked"));

	options.push_back(Sprite("Back To Title"));
	options.push_back(Sprite("Exit"));
	options[0].set_position({ 212, 250 });
	options[1].set_position({ 212, 120 });

	selected = 0;
	confirmed = -1;
	nButtons = options.size();
	wait = 300;
}

Scene_Menu::~Scene_Menu()
{
}

void Scene_Menu::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);

	if (confirmed > -1)
	{
		wait -= elapsedTime;
		if (wait <= 0)
		{
			switch (confirmed)
			{
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

	if (KeyboardManager::is_special_pressed(GLUT_KEY_DOWN))
		selected = (selected + 1) % nButtons;
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_UP))
		selected = abs((selected - 1) % nButtons);
	else if (KeyboardManager::is_key_pressed(' '))
		confirmed = selected;
}

void Scene_Menu::Draw()
{
	SceneManager::DrawSnapShot();
	Scene::Draw();

	for (int i = 0; i < nButtons; ++i)
	{
		Sprite *tmp;
		if (i == confirmed)
			tmp = &button_state[2];
		else if (i == selected)
			tmp = &button_state[1];
		else
			tmp = &button_state[0];

		tmp->set_position(options[i].get_position());
		tmp->Draw();
		options[i].Draw();
	}
}