#include "GameMap.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

GameMap::GameMap(int const & level, Vector2 const & start)
{
	stringstream ss;
	ss << "Level " << level << ".txt";

	ifstream fin(ss.str());
	if (!fin.is_open())
	{
		_loaded = false;
		return;
	}

	fin >> _width >> _height;
	_grid = new char*[_height];
	for (int i = 0; i < _height; ++i)
		_grid[i] = new char[_width];

	for (int r = 0; r < _height; ++r)
		for (int c = 0; c < _width; ++c)
			fin >> _grid[r][c];

	int t1, t2;
	fin >> t1 >> t2;
	_bomberman = { (double)t2 * 32 + start.x, (double)t1 * 32 + start.y };
	_starting_pos = start;

	_loaded = true;
}

GameMap::~GameMap()
{
	delete []_grid;
}

bool GameMap::is_loaded()
{
	return _loaded;
}

Vector2 GameMap::bomberman_starting_pos()
{
	return _bomberman;
}

void GameMap::Update(long long const & totalTime, long long const & elapsedTime)
{

}

void GameMap::Draw()
{
	for (int r = 0; r < _height; ++r)
	{
		for (int c = 0; c < _width; ++c)
		{
			switch (_grid[r][c])
			{
			case '0':
				TextureManager::BindTexture("Grass");
				break;
			case '1':
				TextureManager::BindTexture("Wood");
				break;
			case '2':
				TextureManager::BindTexture("Wall");
				break;
			default:
				TextureManager::BindTexture("Grass");
				break;
			}

			double x = r * 32;
			double y = c * 32;

			glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f); glVertex2d(_starting_pos.x + x, _starting_pos.y + y); // top left
			glTexCoord2d(1.0f, 0.0f); glVertex2d(_starting_pos.x + x + 32, _starting_pos.y + y); // top right
			glTexCoord2d(1.0f, 1.0f); glVertex2d(_starting_pos.x + x + 32, _starting_pos.y + y + 32); // bottom right
			glTexCoord2d(0.0f, 1.0f); glVertex2d(_starting_pos.x + x, _starting_pos.y + y + 32); // bottom left
			glEnd();
		}
	}
}