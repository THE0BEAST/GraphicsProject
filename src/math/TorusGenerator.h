#pragma once

#define _USE_MATH_DEFINES
#include <cmath> 
#include <vector>

#include "Vector3.h"

class TorusGenerator
{
private:
	static Vector3 GetTorusVertice(float u, float v, float d, float d2)
	{
		Vector3 W = Vector3(cos(u), sin(u), 0);
		Vector3 Q = Vector3(0, 0, 0) + (W * d) + (W * cos(v)) * d2 + Vector3(0, 0, d2 * sin(v));

		return Q;
	}

public:
	static void GenerateTorusVertices(std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<Vector2> &uvs,float increments, float d, float d2)
	{
		if (increments < 2) increments = 2;

		for (int i = 0; i < 360; i += increments)
		{
			for (int y = 0; y < 360; y += increments)
			{
				// Vertices
				float radU = i * (M_PI / 180);
				float radV = y * (M_PI / 180);
				float radUNext = (i + increments) * (M_PI / 180);
				float radVNext = (y + increments) * (M_PI / 180);
				float radUPrev = (i - increments) * (M_PI / 180);
				float radVPrev = (y - increments) * (M_PI / 180);

				Vector3 vertex1 = GetTorusVertice(radU, radV, d, d2);
				Vector3 vertex2 = GetTorusVertice(radU, radVNext, d, d2);
				Vector3 vertex3 = GetTorusVertice(radUPrev, radV, d, d2);

				Vector3 vertex4 = GetTorusVertice(radUPrev, radV, d, d2);
				Vector3 vertex5 = GetTorusVertice(radU, radVNext, d, d2);
				Vector3 vertex6 = GetTorusVertice(radUPrev, radVNext, d, d2);

				vertices.push_back(vertex1);
				vertices.push_back(vertex2);
				vertices.push_back(vertex3);

				vertices.push_back(vertex4);
				vertices.push_back(vertex5);
				vertices.push_back(vertex6);

				// UVS

				uvs.push_back(Vector2(1.0f / 360 * i, 1.0f / 360 * y));
				uvs.push_back(Vector2(1.0f / 360 * i, 1.0f / 360 * (y + increments)));
				uvs.push_back(Vector2(1.0f / 360 * (i - increments), 1.0f / 360 * y));

				uvs.push_back(Vector2(1.0f / 360 * (i - increments), 1.0f / 360 * y));
				uvs.push_back(Vector2(1.0f / 360 * i, 1.0f / 360 * (y + increments)));
				uvs.push_back(Vector2(1.0f / 360 * (i - increments), 1.0f / 360 * (y + increments)));

				// Normals
				Vector3 N = Vector3::Normal(vertex1, vertex2, vertex3);
				normals.push_back(N);
				normals.push_back(N);
				normals.push_back(N);

				N = Vector3::Normal(vertex4, vertex5, vertex6);
				normals.push_back(N);
				normals.push_back(N);
				normals.push_back(N);
			}
		}
	}
};