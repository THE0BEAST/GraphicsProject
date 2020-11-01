#pragma once

#include "math/vector3.h"
#include "graphics/texture.h"

class Material
{
public:
	Texture texture;
	Vector3 ambientReflection = Vector3(0.5, 0.5, 0.5);
	Vector3 diffuseReflection = Vector3(0.5, 0.5, 0.5);
	Vector3 specularReflection = Vector3(0.5, 0.5, 0.5);
	float shininess = 100.0;

	Material();
	Material(const char* fileName);
	Material(const char* fileName, Vector3 ambientReflection, Vector3 diffuseReflection, Vector3 specularReflection, float shininess);
};