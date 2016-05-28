#pragma once
#include <stack>
#include "Scene.h"
using namespace std;

class SceneManager
{
private:
	static stack<Scene*> _scenes;

	SceneManager();
	~SceneManager();
public:
	static Scene* CurrentScene();

	// Add new scene to the top of the stack
	static void AddScene(Scene * scene);
	// Change the scene at the top of the stack
	static void ChangeScene(Scene * scene);
	// Return to the previous scene in the stack
	static void ReturnScene();
	// Free resources
	static void CleanUp();
};