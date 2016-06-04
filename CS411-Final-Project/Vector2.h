#pragma once

struct Vector2
{
	double x, y;

	Vector2 operator+(Vector2 const & obj)
	{
		return { x + obj.x, y + obj.y };
	}

	Vector2 operator-(Vector2 const & obj)
	{
		return{ x - obj.x, y - obj.y };
	}
};