#pragma once

#define _USE_MATH_DEFINES
#include <cmath> 
#include "Vector3.h"
#include "GL/glew.h"

struct Matrix4x4
{
	GLfloat elements[16];

	Matrix4x4();
	Matrix4x4(float diagonal);
	Matrix4x4(GLfloat elements[]);

	static Matrix4x4 Perspective(float fov, float aspectRation, float near, float far);
	static Matrix4x4 LookAt(Vector3 position, Vector3 lookAt, Vector3 up);
	static Matrix4x4 Translate(Matrix4x4 matrix, const Vector3 &vector);
	static Matrix4x4 Rotate(Matrix4x4 &matrix, Vector3 &axis, float angle);
	static Matrix4x4 Scale(Matrix4x4 matrix, const Vector3 &vector);

	Matrix4x4 &operator*=(const Matrix4x4 &other);

	friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& matrix);
};

Matrix4x4 operator* (Matrix4x4 &lhs, const Matrix4x4 &rhs);