#include "KeyboardManager.h"

char KeyboardManager::_key = 0;
int KeyboardManager::_special = -1;

void KeyboardManager::set_key(char const & key)
{
	_key = key;
}

void KeyboardManager::set_special(int const & key)
{
	_special = key;
}

bool KeyboardManager:: is_key_pressed(char const & key)
{
	return _key == key;
}

bool KeyboardManager:: is_special_pressed(int const & key)
{
	return _special == key;
}

void KeyboardManager::Reset()
{
	_key = 0;
	_special = -1;
}