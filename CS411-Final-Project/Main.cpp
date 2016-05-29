#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "GameManager.h"
using namespace std;

int main(int argc, char ** argv)
{
	GameManager::Initialize(&argc, argv, WIDTH_WINDOW_SCREEN, HEIGHT_WINDOW_SCREEN);
	GameManager::GameLoop(60);
	GameManager::Shutdown();
	return 0;
}