#pragma once
#include "SceneManager.h"
#include "KeyboardManager.h"

class Scene_Congratulations : public Scene
{
private:
public:
	Scene_Congratulations();
	~Scene_Congratulations();

	void Update(long long const & totalTime, long long const & elapsedTime);
	void Draw();
};