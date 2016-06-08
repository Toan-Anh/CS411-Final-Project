#pragma once
#include "SceneManager.h"
#include "Scene_Level.h"

class Scene_LevelSelection : public Scene
{
private:
	vector<Sprite> button_state;
	vector<Sprite> numbers;
	int current_option;
	int chosen_option;
	vector<Vector2> option_positions;

	long long transition_wait_time;

	void DrawOneDigit(unsigned const & number, vector<Vector2> const & rect);
	void DrawTwoDigits(unsigned const & number, vector<Vector2> const & rect);
	void DrawBestScore(unsigned const & score);
public:
	Scene_LevelSelection();
	~Scene_LevelSelection();

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};