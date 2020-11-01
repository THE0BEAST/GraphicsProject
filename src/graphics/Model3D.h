#pragma once

#include <vector>

#include "math\Matrix4x4.h"
#include "Material.h"
#include "Utils\FileReaders.h"

class Model3D
{
public:
	Material* material;

	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Vector2> uvs;
	bool triangulated;

	Matrix4x4 modelMatrix;

	Model3D();
	Model3D(const char* fileName);
	Model3D(std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<Vector2> &uvs);

	Matrix4x4 GetModelMatrix();
	void Translate(Vector3 vector);
	void Rotate(Vector3 vector, float angle);
	void Scale(Vector3 vector);
};