#include "Scene_LevelSelection.h"
#include <fstream>
using namespace std;

unordered_set<int> UnlockedLevels;
unordered_map<int, int> BestScores;

Scene_LevelSelection::Scene_LevelSelection()
{
	_sprites.push_back(new Sprite("Level Selection"));

	button_state.push_back(Sprite("Button Normal Small"));
	button_state.push_back(Sprite("Button Highlight Small"));
	button_state.push_back(Sprite("Button Selected Small"));
	button_state.push_back(Sprite("Button Locked Small"));
	button_state.push_back(Sprite("Button Locked Lock Small"));

	for (int i = 0; i < 10; ++i)
		numbers.push_back(Sprite("Num_" + to_string(i)));

	_sprites[0]->set_position({ 20, 0 });

	// 15 levels on a page only
	for (int i = 0; i < N_LEVELS && i < 15; ++i)
		option_positions.push_back({ (double)78 + (i % 5) * 92 + 20, (double)294 - (i / 5) * 87 });

	UnlockedLevels.insert(1);
	BestScores[1] = 0;

	ifstream fin;
	fin.open("GameData");
	if (fin.is_open())
	{
		int level, best;
		while (fin >> level >> best)
		{
			UnlockedLevels.insert(level);
			BestScores[level] = best;
		}
		fin.close();
	}

	current_option = 0;
	chosen_option = -1;
	transition_wait_time = 150;
}

Scene_LevelSelection::~Scene_LevelSelection()
{
}

void Scene_LevelSelection::DrawOneDigit(unsigned const & number, vector<Vector2> const & rect)
{
	if (number < 0 || number > 9 || rect.size() != 4)
		return;

	double x = rect[0].x + (rect[1].x - rect[0].x - WIDTH_SCORE_NUM) / 2;
	double y = rect[0].y + (rect[3].y - rect[0].y - HEIGHT_SCORE_NUM) / 2;

	numbers[number].set_position({ x, y });
	numbers[number].Draw();
}

void Scene_LevelSelection::DrawTwoDigits(unsigned const & number, vector<Vector2> const & rect)
{
	if (number < 10 || number > 99 || rect.size() != 4)
		return;

	double x = rect[0].x + (rect[1].x - rect[0].x - WIDTH_SCORE_NUM) / 2;
	double y = rect[0].y + (rect[3].y - rect[0].y - HEIGHT_SCORE_NUM) / 2;

	numbers[number / 10].set_position({ x - WIDTH_SCORE_NUM, y });
	numbers[number / 10].Draw();

	numbers[number % 10].set_position({ x + WIDTH_SCORE_NUM, y });
	numbers[number % 10].Draw();
}

void Scene_LevelSelection::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);


	if (chosen_option > -1)
	{
		transition_wait_time -= elapsedTime;
		if (transition_wait_time <= 0)
		{
			SceneManager::AddScene(new Scene_Level(current_option + 1));
			chosen_option = -1;
			transition_wait_time = 150;
		}
		return;
	}


	int n = N_LEVELS < 15 ? N_LEVELS : 15;

	if (KeyboardManager::is_special_pressed(GLUT_KEY_LEFT))
	{
		for (int i = 1; i <= n; ++i)
		{
			if (UnlockedLevels.find((current_option - i + n) % n + 1) != UnlockedLevels.end())
			{
				current_option = (current_option - i + n) % n;
				break;
			}
		}
	}
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_RIGHT))
	{
		for (int i = 1; i <= n; ++i)
		{
			if (UnlockedLevels.find((current_option + i) % n + 1) != UnlockedLevels.end())
			{
				current_option = (current_option + i) % n;
				break;
			}
		}
	}
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_UP))
	{
		for (int i = 5; i <= n; i += 5)
		{
			if (UnlockedLevels.find((current_option - i + n) % n + 1) != UnlockedLevels.end())
			{
				current_option = (current_option - i + n) % n;
				break;
			}
		}
	}
	else if (KeyboardManager::is_special_pressed(GLUT_KEY_DOWN))
	{
		for (int i = 5; i <= n; i += 5)
		{
			if (UnlockedLevels.find((current_option + i) % n + 1) != UnlockedLevels.end())
			{
				current_option = (current_option + i) % n;
				break;
			}
		}
	}
	else if (KeyboardManager::is_key_pressed(' '))
	{
		chosen_option = current_option;
	}
}

void Scene_LevelSelection::DrawBestScore(unsigned const & score)
{
	int tmp = score, digit, i = 4;
	Vector2 base_pos = { 320, 32 };

	while (i >= 0)
	{
		digit = tmp % 10;
		numbers[digit].set_position({ base_pos.x + WIDTH_SCORE_NUM * i, base_pos.y });
		numbers[digit].Draw();
		tmp /= 10;
		--i;
	}
}

void Scene_LevelSelection::Draw()
{
	Scene::Draw();

	for (int i = 0; i < N_LEVELS && i < 15; ++i)
	{
		Sprite *tmp;
		if (UnlockedLevels.find(i + 1) != UnlockedLevels.end())
		{
			if (i == chosen_option)
				tmp = &button_state[2];
			else if (i == current_option)
				tmp = &button_state[1];
			else
				tmp = &button_state[0];
		}
		else
			tmp = &button_state[4];

		tmp->set_position(option_positions[i]);
		tmp->Draw();

		if (UnlockedLevels.find(i + 1) != UnlockedLevels.end())
		{
			if (i + 1 < 10)
				DrawOneDigit(i + 1, tmp->get_rect());
			else
				DrawTwoDigits(i + 1, tmp->get_rect());
		}
	}

	DrawBestScore(BestScores[current_option + 1]);
}