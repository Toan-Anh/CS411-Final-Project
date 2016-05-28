#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "GameManager.h"
using namespace std;

int main(int argc, char ** argv)
{
	GameManager::Initialize(&argc, argv, 640, 480);
	GameManager::GameLoop(60);
	GameManager::Shutdown();
	return 0;
}