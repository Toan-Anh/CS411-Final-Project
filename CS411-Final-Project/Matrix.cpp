#include "Matrix.h"
#include <cmath>
using namespace std;

Matrix::Matrix()
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (i == j)
				data[i][j] = 1;
			else
				data[i][j] = 0;
}

Matrix::Matrix(const Matrix &obj)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			data[i][j] = obj.data[i][j];
}

Matrix::Matrix(const double &m11, const double &m12, const double &m21, const double &m22, const double &dx, const double &dy)
{
	data[0][0] = m11;
	data[0][1] = m12;
	data[1][0] = m21;
	data[1][1] = m22;
	data[2][0] = dx;
	data[2][1] = dy;
	data[0][2] = 0;
	data[1][2] = 0;
	data[2][2] = 1;
}

double* Matrix::Elements()
{
	double arr[9];
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			arr[i * 3 + j] = data[i][j];
	return arr;
}

double Matrix::Determinant()
{
	Matrix tmp(*this);
	double det = 1;
	for (int i = 0; i < 3; ++i)
	{
		for (int k = i + 1; k < 3; ++k)
		{
			if (tmp.data[i][i] == 0)
			{
				int row_to_swap;
				for (row_to_swap = k; row_to_swap < 3 && tmp.data[row_to_swap][i] == 0; ++row_to_swap);
				if (row_to_swap < 3)
				{
					for (int j = 0; j < 3; ++j)
					{
						double t = tmp.data[row_to_swap][j];
						tmp.data[row_to_swap][j] = tmp.data[i][j];
						tmp.data[i][j] = t;
					}
					det *= -1;
				}
				else
					return 0;
			}

			double ratio = tmp.data[k][i] / tmp.data[i][i];
			for (int j = 0; j < 3; ++j)
			{
				tmp.data[k][j] = tmp.data[k][j] - tmp.data[i][j] * ratio;
			}
		}
		det *= tmp.data[i][i];
	}
	return det;
}


void Matrix::Reset()
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (i == j)
				data[i][j] = 1;
			else
				data[i][j] = 0;
}

void Matrix::Invert()
{
	if (Determinant() == 0)
	{
		//cout << "The matrix cannot be inverted." << endl;
		return;
	}

	Matrix tmp(*this);
	this->Reset();
	
	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			if (i != k)
			{
				if (tmp.data[i][i] == 0)
				{
					int row_to_swap;
					for (row_to_swap = i + 1; row_to_swap < 3 && tmp.data[row_to_swap][i] == 0; ++row_to_swap);
					if (row_to_swap < 3)
					{
						for (int j = 0; j < 3; ++j)
						{
							double t = tmp.data[row_to_swap][j];
							tmp.data[row_to_swap][j] = tmp.data[i][j];
							tmp.data[i][j] = t;

							t = data[row_to_swap][j];
							data[row_to_swap][j] = data[i][j];
							data[i][j] = t;
						}
					}
				}

				double ratio = tmp.data[k][i] / tmp.data[i][i];
				for (int j = 0; j < 3; ++j)
				{
					tmp.data[k][j] = tmp.data[k][j] - tmp.data[i][j] * ratio;
					data[k][j] = data[k][j] - data[i][j] * ratio;
				}
			}
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		double ratio = 1 / tmp.data[i][i];
		for (int j = 0; j < 3; ++j)
		{
			data[i][j] *= ratio;
		}
	}
}

void Matrix::Rotate(const double &angle)
{
	double radian = angle * PI / 180.0;
	Matrix rotate(cos(radian), sin(radian), -sin(radian), cos(radian), 0, 0);
	this->Copy(*this * rotate);
}

void Matrix::Translate(const double &offsetX, const double &offsetY)
{
	Matrix translate(1, 0, 0, 1, offsetX, offsetY);
	this->Copy(*this * translate);
}

void Matrix::Scale(const double &scaleX, const double &scaleY)
{
	Matrix scale(scaleX, 0, 0, scaleY, 0, 0);
	this->Copy(*this * scale);
}

void Matrix::Shear(const double &shearX, const double &shearY)
{
	Matrix shear(1, shearY, shearX, 1, 0, 0);
	this->Copy(*this * shear);
}

Matrix& Matrix::Multiply(const Matrix &other)
{
	Matrix tmp;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			double calc = 0;
			for (int k = 0; k < 3; ++k)
				calc += data[i][k] * other.data[k][j];
			tmp.data[i][j] = calc;
		}
	}
	return tmp;
}

void Matrix::TransformPoint(Vector2 &point) const
{
	double x = point.x;
	double y = point.y;
	point.x = x * data[0][0] + y * data[1][0] + data[2][0];
	point.y = x * data[0][1] + y * data[1][1] + data[2][1];
}

void Matrix::TransformPoints(vector<Vector2> &points) const
{
	for (unsigned int i = 0; i < points.size(); ++i)
		TransformPoint(points[i]);
}

Matrix& Matrix::operator*(const Matrix &other)
{
	return this->Multiply(other);
}

Matrix& Matrix::operator=(const Matrix &other)
{
	return Matrix(other);
}

void Matrix::Copy(const Matrix &other)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			data[i][j] = other.data[i][j];
}