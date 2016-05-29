#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>
#include <string>
#include "TextureManager.h"
#include "SceneManager.h"
#include "KeyboardManager.h"
#include "Sprite.h"
#include "Scene.h"
#include "Scene_Start.h"
using namespace std;

class GameManager
{
private:
	static GameManager* instance;
	static bool _running;
	static unsigned long long current_time;
	static SceneManager _scene_manager;

	// private constructors / destructor
	GameManager();
	~GameManager();

	// represent game update routine
	static void update(long long const & totalTime, long long const & elapsedTime);

	// callbacks
	static void draw(); // game render routine
	static void keyboard_handler(unsigned char key, int x, int y);
	static void special_handler(int key, int x, int y);
	static void reshape(int width, int height);
public:
	static void Initialize(int *argcp, char **argv, int const & win_width, int const & win_height);
	static void GameLoop(int frame_rate);
	static void ExitGame();
	static void Shutdown();
};