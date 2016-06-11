#pragma once
#include <vector>
#include "Vector2.h"

using std::vector;

const float PI = 3.1415926f;

//=============================================================================
//        class Matrix
// - The class is implemented following the lecture slides.
// - When calling Rotate(), Translate(), Scale(), and Shear(), the 
// new matrices will be APPENDED to the current matrix instead of prepending.
//=============================================================================

class Matrix
{
private:
	double data[3][3];
public:
	Matrix();
	Matrix(const Matrix &obj);
	Matrix(const double &m11, const double &m12, const double &m21, const double &m22, const double &dx, const double &dy);

	double* Elements();
	double Determinant();

	void Reset();
	void Invert();
	void Rotate(const double &angle);
	void Translate(const double &offsetX, const double &offsetY);
	void Scale(const double &scaleX, const double &scaleY);
	void Shear(const double &shearX, const double &shearY);

	Matrix& Multiply(const Matrix &other);

	Vector2 TransformPoint(Vector2 point) const;
	vector<Vector2> TransformPoints(vector<Vector2> points) const;

	Matrix& operator*(const Matrix &other);
	Matrix& operator=(const Matrix &other);
	void Copy(const Matrix &other);
};

//=============================================================================