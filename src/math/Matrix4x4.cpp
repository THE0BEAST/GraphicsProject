#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
	for (int i = 0; i < 4 * 4; ++i)
		elements[i] = 0.0f;
}

Matrix4x4::Matrix4x4(float diagonal)
{
	for (int i = 0; i < 4 * 4; ++i)
		elements[i] = 0.0f;

	elements[0] = diagonal;
	elements[5] = diagonal;
	elements[10] = diagonal;
	elements[15] = diagonal;
}

Matrix4x4::Matrix4x4(GLfloat elements[])
{
	for (int i = 0; i < 16; ++i)
	{
		this->elements[i] = elements[i];
	}
}

Matrix4x4 Matrix4x4::Perspective(float fov, float aspectRation, float near, float far)
{
	Matrix4x4 result;

	float tanHalfFovy = tan(fov / 2);

	result.elements[0 + 0 * 4] = 1.0f / (aspectRation * tanHalfFovy);
	result.elements[1 + 1 * 4] = 1.0f / tanHalfFovy;
	result.elements[2 + 2 * 4] = (far + near) / (near - far);
	result.elements[3 + 2 * 4] = -1.0f;
	result.elements[2 + 3 * 4] = 2.0f * far * near / (near - far);

	return result;
}

Matrix4x4 Matrix4x4::LookAt(Vector3 position, Vector3 lookAt, Vector3 up)
{
	Matrix4x4 result = Matrix4x4(1.0f);

	Vector3 f = (lookAt - position).Normalized();
	Vector3 s = Vector3::Cross(f, up).Normalized();
	Vector3 u = Vector3::Cross(s, f);

	result.elements[0 + 0 * 4] = s.x;
	result.elements[0 + 1 * 4] = s.y;
	result.elements[0 + 2 * 4] = s.z;

	result.elements[1 + 0 * 4] = u.x;
	result.elements[1 + 1 * 4] = u.y;
	result.elements[1 + 2 * 4] = u.z;

	result.elements[2 + 0 * 4] = -f.x;
	result.elements[2 + 1 * 4] = -f.y;
	result.elements[2 + 2 * 4] = -f.z;

	result = Matrix4x4::Translate(result, Vector3(-position.x, -position.y, -position.z));

	return result;
}

Matrix4x4 Matrix4x4::Translate(Matrix4x4 matrix, const Vector3 &vector)
{
	Matrix4x4 result(1.0f);

	result.elements[0 + 3 * 4] = vector.x;
	result.elements[1 + 3 * 4] = vector.y;
	result.elements[2 + 3 * 4] = vector.z;

	return result;
}

Matrix4x4 Matrix4x4::Rotate(Matrix4x4 &matrix, Vector3 &axis, float angle)
{
	Matrix4x4 result(1.0f);

	float R2D = M_PI / 180;
	float r = angle * R2D;
	float c = cos(r);
	float s = sin(r);
	float omc = 1.0f - c;

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	result.elements[0 + 0 * 4] = x * x * omc + c;
	result.elements[0 + 1 * 4] = y * x * omc + z * s;
	result.elements[0 + 2 * 4] = x * z * omc - y * s;

	result.elements[1 + 0 * 4] = x * y * omc - z * s;
	result.elements[1 + 1 * 4] = y * y * omc + c;
	result.elements[1 + 2 * 4] = y * z * omc + x * s;

	result.elements[2 + 0 * 4] = x * z * omc + y * s;
	result.elements[2 + 1 * 4] = y * z * omc - x * s;
	result.elements[2 + 2 * 4] = z * z * omc + c;

	return matrix * result;
}

Matrix4x4 Matrix4x4::Scale(Matrix4x4 matrix, const Vector3 &vector)
{
	Matrix4x4 result(1.0f);

	result.elements[0 + 0 * 4] = vector.x;
	result.elements[1 + 1 * 4] = vector.y;
	result.elements[2 + 2 * 4] = vector.z;

	return result * matrix;
}

Matrix4x4 operator*(Matrix4x4 & lhs, const Matrix4x4 & rhs)
{
	Matrix4x4 result;

	result.elements[0] = lhs.elements[0] * rhs.elements[0] + lhs.elements[1] * rhs.elements[4] + lhs.elements[2] * rhs.elements[8] + lhs.elements[3] * rhs.elements[12];
	result.elements[1] = lhs.elements[0] * rhs.elements[1] + lhs.elements[1] * rhs.elements[5] + lhs.elements[2] * rhs.elements[9] + lhs.elements[3] * rhs.elements[13];
	result.elements[2] = lhs.elements[0] * rhs.elements[2] + lhs.elements[1] * rhs.elements[6] + lhs.elements[2] * rhs.elements[10] + lhs.elements[3] * rhs.elements[14];
	result.elements[3] = lhs.elements[0] * rhs.elements[3] + lhs.elements[1] * rhs.elements[7] + lhs.elements[2] * rhs.elements[11] + lhs.elements[3] * rhs.elements[15];

	result.elements[4] = lhs.elements[4] * rhs.elements[0] + lhs.elements[5] * rhs.elements[4] + lhs.elements[6] * rhs.elements[8] + lhs.elements[7] * rhs.elements[12];
	result.elements[5] = lhs.elements[4] * rhs.elements[1] + lhs.elements[5] * rhs.elements[5] + lhs.elements[6] * rhs.elements[9] + lhs.elements[7] * rhs.elements[13];
	result.elements[6] = lhs.elements[4] * rhs.elements[2] + lhs.elements[5] * rhs.elements[6] + lhs.elements[6] * rhs.elements[10] + lhs.elements[7] * rhs.elements[14];
	result.elements[7] = lhs.elements[4] * rhs.elements[3] + lhs.elements[5] * rhs.elements[7] + lhs.elements[6] * rhs.elements[11] + lhs.elements[7] * rhs.elements[15];

	result.elements[8] = lhs.elements[8] * rhs.elements[0] + lhs.elements[9] * rhs.elements[4] + lhs.elements[10] * rhs.elements[8] + lhs.elements[11] * rhs.elements[12];
	result.elements[9] = lhs.elements[8] * rhs.elements[1] + lhs.elements[9] * rhs.elements[5] + lhs.elements[10] * rhs.elements[9] + lhs.elements[11] * rhs.elements[13];
	result.elements[10] = lhs.elements[8] * rhs.elements[2] + lhs.elements[9] * rhs.elements[6] + lhs.elements[10] * rhs.elements[10] + lhs.elements[11] * rhs.elements[14];
	result.elements[11] = lhs.elements[8] * rhs.elements[3] + lhs.elements[9] * rhs.elements[7] + lhs.elements[10] * rhs.elements[11] + lhs.elements[11] * rhs.elements[15];

	result.elements[12] = lhs.elements[12] * rhs.elements[0] + lhs.elements[13] * rhs.elements[4] + lhs.elements[14] * rhs.elements[8] + lhs.elements[15] * rhs.elements[12];
	result.elements[13] = lhs.elements[12] * rhs.elements[1] + lhs.elements[13] * rhs.elements[5] + lhs.elements[14] * rhs.elements[9] + lhs.elements[15] * rhs.elements[13];
	result.elements[14] = lhs.elements[12] * rhs.elements[2] + lhs.elements[13] * rhs.elements[6] + lhs.elements[14] * rhs.elements[10] + lhs.elements[15] * rhs.elements[14];
	result.elements[15] = lhs.elements[12] * rhs.elements[3] + lhs.elements[13] * rhs.elements[7] + lhs.elements[14] * rhs.elements[11] + lhs.elements[15] * rhs.elements[15];

	return result;
}

Matrix4x4 &Matrix4x4::operator*=(const Matrix4x4& other)
{
	this->elements[0] = this->elements[0] * other.elements[0] + this->elements[1] * other.elements[4] + this->elements[2] * other.elements[8] + this->elements[3] * other.elements[12];
	this->elements[1] = this->elements[0] * other.elements[1] + this->elements[1] * other.elements[5] + this->elements[2] * other.elements[9] + this->elements[3] * other.elements[13];
	this->elements[2] = this->elements[0] * other.elements[2] + this->elements[1] * other.elements[6] + this->elements[2] * other.elements[10] + this->elements[3] * other.elements[14];
	this->elements[3] = this->elements[0] * other.elements[3] + this->elements[1] * other.elements[7] + this->elements[2] * other.elements[11] + this->elements[3] * other.elements[15];

	this->elements[4] = this->elements[4] * other.elements[0] + this->elements[5] * other.elements[4] + this->elements[6] * other.elements[8] + this->elements[7] * other.elements[12];
	this->elements[5] = this->elements[4] * other.elements[1] + this->elements[5] * other.elements[5] + this->elements[6] * other.elements[9] + this->elements[7] * other.elements[13];
	this->elements[6] = this->elements[4] * other.elements[2] + this->elements[5] * other.elements[6] + this->elements[6] * other.elements[10] + this->elements[7] * other.elements[14];
	this->elements[7] = this->elements[4] * other.elements[3] + this->elements[5] * other.elements[7] + this->elements[6] * other.elements[11] + this->elements[7] * other.elements[15];

	this->elements[8] = this->elements[8] * other.elements[0] + this->elements[9] * other.elements[4] + this->elements[10] * other.elements[8] + this->elements[11] * other.elements[12];
	this->elements[9] = this->elements[8] * other.elements[1] + this->elements[9] * other.elements[5] + this->elements[10] * other.elements[9] + this->elements[11] * other.elements[13];
	this->elements[10] = this->elements[8] * other.elements[2] + this->elements[9] * other.elements[6] + this->elements[10] * other.elements[10] + this->elements[11] * other.elements[14];
	this->elements[11] = this->elements[8] * other.elements[3] + this->elements[9] * other.elements[7] + this->elements[10] * other.elements[11] + this->elements[11] * other.elements[15];

	this->elements[12] = this->elements[12] * other.elements[0] + this->elements[13] * other.elements[4] + this->elements[14] * other.elements[8] + this->elements[15] * other.elements[12];
	this->elements[13] = this->elements[12] * other.elements[1] + this->elements[13] * other.elements[5] + this->elements[14] * other.elements[9] + this->elements[15] * other.elements[13];
	this->elements[14] = this->elements[12] * other.elements[2] + this->elements[13] * other.elements[6] + this->elements[14] * other.elements[10] + this->elements[15] * other.elements[14];
	this->elements[15] = this->elements[12] * other.elements[3] + this->elements[13] * other.elements[7] + this->elements[14] * other.elements[11] + this->elements[15] * other.elements[15];
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix4x4& matrix)
{
	os << "Matrix4x4(" << matrix.elements[0] << ", " << matrix.elements[1] << ", " << matrix.elements[2] << ", " << matrix.elements[3] << std::endl;
	os << "          " << matrix.elements[4] << ", " << matrix.elements[5] << ", " << matrix.elements[6] << ", " << matrix.elements[7] << std::endl;
	os << "          " << matrix.elements[8] << ", " << matrix.elements[9] << ", " << matrix.elements[10] << ", " << matrix.elements[11] << std::endl;
	os << "          " << matrix.elements[12] << ", " << matrix.elements[13] << ", " << matrix.elements[14] << ", " << matrix.elements[15] << ")" << std::endl;
	return os;
}