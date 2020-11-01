#include "Model3D.h"

Model3D::Model3D() {}

Model3D::Model3D(const char *fileName)
{
	loadOBJ(fileName, vertices, uvs, normals);
	modelMatrix = Matrix4x4(1.0f);
}

Model3D::Model3D(std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<Vector2> &uvs)
{
	this->vertices = vertices;
	this->normals = normals;
	this->uvs = uvs;
	modelMatrix = Matrix4x4(1.0f);
}

Matrix4x4 Model3D::GetModelMatrix()
{
	return modelMatrix;
}

void Model3D::Translate(Vector3 vector)
{
	modelMatrix = Matrix4x4::Translate(modelMatrix, vector);
}

void Model3D::Rotate(Vector3 vector, float angle)
{
	modelMatrix = Matrix4x4::Rotate(modelMatrix, vector, angle);
}

void Model3D::Scale(Vector3 vector)
{
	modelMatrix = Matrix4x4::Scale(modelMatrix, vector);
}