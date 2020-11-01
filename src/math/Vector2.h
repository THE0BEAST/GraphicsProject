#pragma once

#include <math.h>
#include <iostream> 

struct Vector2
{
	float x, y;

	Vector2();
	Vector2(const float x, const float y);

	float Magnitude() const;
	Vector2 Normalized() const;
	static Vector2 One();
	static Vector2 Zero();

	Vector2 operator+ (Vector2 &other) const;
	Vector2 operator- (Vector2 &other) const;
	void operator+= (Vector2 &other);
	void operator-= (Vector2 &other);
	Vector2 operator* (const float other) const;
	Vector2 operator/ (const float other) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);
};