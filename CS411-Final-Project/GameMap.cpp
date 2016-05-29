#include "GameMap.h"
#include <sstream>
#include <fstream>
using namespace std;

GameMap::GameMap(int const & level)
{
	stringstream ss;
	ss << "Level " << level << ".txt";

	ifstream fin(ss.str());
	if (!fin.is_open())
	{
		loaded = false;
		return;
	}

	int width, height;
	fin >> width >> height;
	grid = new char*[height];
	for (int i = 0; i < height; ++i)
		grid[i] = new char[width];

	for (int r = 0; r < height; ++r)
		for (int c = 0; c < width; ++c)
			fin >> grid[r][c];

	loaded = true;
}

GameMap::~GameMap()
{
	delete []grid;
}

bool GameMap::is_loaded()
{
	return loaded;
}