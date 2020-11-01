#pragma once

#include <math.h>
#include <iostream> 
#include <vector>

struct Vector3
{
	float x, y, z;

	Vector3();
	Vector3(const float x, const float y, const float z);

	float Magnitude();
	Vector3 Normalized();

	static Vector3 One();
	static Vector3 Zero();
	static Vector3 Up();
	static float Dot(const Vector3 &A, const Vector3 &B);
	static Vector3 Cross(const Vector3 &A, const Vector3 &B);
	static Vector3 Normal(Vector3 &A, Vector3 &B, Vector3 &C);

	Vector3 operator+ (Vector3 &other) const;
	Vector3 operator- (Vector3 &other) const;
	void operator+= (Vector3 &other);
	void operator-= (Vector3 &other);
	Vector3 operator* (const float other) const;
	Vector3 operator/ (const float other) const;
	bool operator== (Vector3 &other) const;
	bool operator!= (Vector3 &other) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector3& vector);
};