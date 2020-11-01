#include "Vector2.h"

Vector2::Vector2() : x(0), y(0)
{}

Vector2::Vector2(const float x, const float y) : x(x), y(y)
{}

float Vector2::Magnitude() const
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::Normalized() const
{
	float m = Magnitude();
	return Vector2(x / m, y / m);
}

Vector2 Vector2::One()
{
	return Vector2(1, 1);
}

Vector2 Vector2::Zero()
{
	return Vector2(0, 0);
}

Vector2 Vector2::operator+ (Vector2 &other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator- (Vector2 &other) const
{
	return Vector2(x - other.x, y - other.y);
}

void Vector2::operator+= (Vector2 &other)
{
	x += other.x;
	y += other.y;
}

void Vector2::operator-= (Vector2 &other)
{
	x -= other.x;
	y -= other.y;
}

Vector2 Vector2::operator* (const float other) const
{
	return Vector2(x * other, y * other);
}

Vector2 Vector2::operator/ (const float other) const
{
	return Vector2(x / other, y / other);
}

std::ostream& operator<<(std::ostream& os, const Vector2& vector)
{
	os << "Vector2(" << vector.x << ", " << vector.y << ")";
	return os;
}