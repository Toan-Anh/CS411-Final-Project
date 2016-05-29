#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>
#include <vector>
#include "Matrix.h"
#include "TextureManager.h"
using namespace std;

class Sprite
{
protected:
	Vector2 _size;
	vector<Vector2> _rect;
	string _name;
public:
	Sprite(string const &name);
	virtual ~Sprite();

	virtual void set_position(Vector2 top_left);
	virtual Vector2 get_position();
	virtual void ApplyMatrix(Matrix const & matrix);
	virtual void Update();
	virtual void Draw();
	
	virtual void move_left() {};
	virtual void move_right() {};
	virtual void move_up() {};
	virtual void move_down() {};
	virtual void put_boom() {};
};