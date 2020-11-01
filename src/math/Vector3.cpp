#include "Vector3.h"

Vector3::Vector3() : x(0), y(0), z(0)
{}

Vector3::Vector3(const float x, const float y, const float z) : x(x), y(y), z(z)
{}


Vector3 Vector3::One()
{
	return Vector3(1, 1, 1);
}

Vector3 Vector3::Zero()
{
	return Vector3(0, 0, 0);
}

Vector3 Vector3::Up()
{
	return Vector3(0, 1, 0);
}

float Vector3::Magnitude()
{
	return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::Normalized() 
{
	float m = Magnitude();
	return Vector3(x / m, y / m, z / m);
}

Vector3 Vector3::Normal(Vector3 &A, Vector3 &B, Vector3 &C)
{
	Vector3 dir = Vector3::Cross(B - A, C - A);
	return dir.Normalized();
}

float Vector3::Dot(const Vector3 &A, const Vector3 &B)
{
	return A.x * B.x + A.y * B.y + A.z * B.z;
}

Vector3 Vector3::Cross(const Vector3 &A, const Vector3 &B)
{
	Vector3 v;
	v.x = A.y * B.z - A.z * B.y;
	v.y = A.z * B.x - A.x * B.z;
	v.z = A.x * B.y - A.y * B.x;
	return v;
}

Vector3 Vector3::operator+ (Vector3 &other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator- (Vector3 &other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

void Vector3::operator+= (Vector3 &other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vector3::operator-= (Vector3 &other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

Vector3 Vector3::operator* (const float other) const
{
	return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator/ (const float other) const
{
	return Vector3(x / other, y / other, z / other);
}

bool Vector3::operator==(Vector3& other) const
{
	if (x == other.x && y == other.y && z == other.z)
		return true;
	else
		return false;
}

bool Vector3::operator!=(Vector3& other) const
{
	if (x == other.x && y == other.y && z == other.z)
		return false;
	else
		return true;
}

std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << "Vector3(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return os;
}
