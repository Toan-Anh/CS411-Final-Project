#include "Scene_Level.h"

Scene_Level::Scene_Level(int const & level) : _map(level, { 160, 0 })
{
	_sprites.push_back(new Bomberman(_map));	
	if (_map.is_loaded())
		_sprites[0]->set_position(_map.bomberman_starting_pos());

	vector<int> info = _map.get_monster_info();
	int nMonsters = info[0];
	for (int i = 0, k = 1; i < nMonsters; ++i)
	{
		int monster_type = info[k++];
		int monster_row = info[k++];
		int monster_column = info[k++];

		if (monster_type == 0)
		{
			int nPaths = info[k++];
			vector<pair<int, int>> paths;
			for (int j = 0; j < nPaths; ++j)
			{
				int t1 = info[k++], t2 = info[k++];
				paths.push_back({ t1, t2 });
			}

			Vector2 monster_pos = _map.Get_Position_From_Grid(monster_row, monster_column);
			_monsters.push_back(new SimpleMonster("Monster 0", _map, monster_pos, paths));
		}
	}

	_monster_killed = 0;

	Vector2 startPos = { 0 , 5 };
	for (int i = 0; i < 5; ++i) {
		_sprites.push_back(new Sprite("Num_0"));

		Vector2 pos = { i*WIDTH_SCORE_NUM, 0 };
		_sprites[i + 1]->set_position(startPos + pos);
	}

}

Scene_Level::~Scene_Level()
{
	for (int i = _monsters.size() - 1; i >= 0; --i)
	{
		if (_monsters[i] != nullptr)
			delete _monsters[i];
		_monsters.pop_back();
	}
}

void Scene_Level::UpdateScore()
{
	// The number of digits of Score must be less than six;
	int score = Score, n, num, i = 4;
	
	while (score != 0)
	{
		num = score % 10;
		Vector2 prePos =_sprites[i + 1]->get_position();
		delete _sprites[i + 1];
		_sprites[i + 1] = new Sprite("Num_" + to_string(num));
		_sprites[i + 1]->set_position(prePos);
		score /= 10;
		--i;
	}

	++Score;
	if (Score > 99999)
		Score = 0;
}

void Scene_Level::Update(long long const & totalTime, long long const & elapsedTime)
{
	Scene::Update(totalTime, elapsedTime);

	for (unsigned i = 0; i < _monsters.size(); ++i)
	{
		if (_monsters[i] != nullptr)
		{
			_monsters[i]->Update(totalTime, elapsedTime);
			if (!_monsters[i]->IsAlive())
			{
				delete _monsters[i];
				_monsters[i] = nullptr;
				++_monster_killed;
			}
		}
	}

	if (_monster_killed == _monsters.size())
		SceneManager::ReturnScene();

	if (!((Bomberman*)_sprites[0])->IsAlive())
		SceneManager::ChangeScene(new Scene_GameOver());

	if (KeyboardManager::is_key_pressed('\r') ||
		KeyboardManager::is_key_pressed('\n'))
	{
		SceneManager::SnapShot();
		SceneManager::AddScene(new Scene_Menu());
	}

	UpdateScore();

}


void Scene_Level::Draw()
{
	if (_map.is_loaded())
		_map.Draw();

	for (unsigned i = 0; i < _monsters.size(); ++i)
		if (_monsters[i] != nullptr)
			_monsters[i]->Draw();

	Scene::Draw();
}