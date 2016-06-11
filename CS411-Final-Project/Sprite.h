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
	vector<Vector2> _tmp_rect;
	string _name;
public:
	Sprite(string const &name);
	virtual ~Sprite();

	virtual void set_position(Vector2 top_left);
	virtual Vector2 get_position();
	virtual vector<Vector2> get_rect();
	virtual void ApplyMatrix(Matrix const & matrix);
	virtual void Update(long long const & totalTime, long long const &elapsedTime);
	virtual void Draw();
};