#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>

class KeyboardManager
{
	friend class GameManager;
private:
	static char _key;
	static int _special;

	static void set_key(char const & key);
	static void set_special(int const & key);

public:
	static bool is_key_pressed(char const & key);
	static bool is_special_pressed(int const & key);

	static void Reset();
};